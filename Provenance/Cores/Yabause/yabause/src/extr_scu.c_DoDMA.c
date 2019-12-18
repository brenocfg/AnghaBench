#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 void* BSWAP16 (int const) ; 
 int /*<<< orphan*/  Cs2RapidCopyT2 (int /*<<< orphan*/ *,int) ; 
 void* DMAMemoryPointer (int) ; 
 int* DMAMemoryType ; 
 int /*<<< orphan*/ * HighWram ; 
 int /*<<< orphan*/ * LowWram ; 
 int /*<<< orphan*/  M68KWriteNotify (int,int) ; 
 int MappedMemoryReadLong (int) ; 
 int MappedMemoryReadWord (int) ; 
 int /*<<< orphan*/  MappedMemoryWriteLong (int,int) ; 
 int /*<<< orphan*/  MappedMemoryWriteWord (int,int) ; 
 int /*<<< orphan*/  SH2WriteNotify (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void DoDMA(u32 ReadAddress, unsigned int ReadAdd,
                  u32 WriteAddress, unsigned int WriteAdd,
                  u32 TransferSize)
{
   if (ReadAdd == 0) {
      // DMA fill

#ifdef OPTIMIZED_DMA
      if (ReadAddress == 0x25818000 && WriteAdd == 4) {
         // Reading from the CD buffer, so optimize if possible.
         if ((WriteAddress & 0x1E000000) == 0x06000000) {
            Cs2RapidCopyT2(&HighWram[WriteAddress & 0xFFFFF], TransferSize/4);
            SH2WriteNotify(WriteAddress, TransferSize);
            return;
         }
         else if ((WriteAddress & 0x1FF00000) == 0x00200000) {
            Cs2RapidCopyT2(&LowWram[WriteAddress & 0xFFFFF], TransferSize/4);
            SH2WriteNotify(WriteAddress, TransferSize);
            return;
         }
      }
#endif

      // Is it a constant source or a register whose value can change from
      // read to read?
      int constant_source = ((ReadAddress & 0x1FF00000) == 0x00200000)
                         || ((ReadAddress & 0x1E000000) == 0x06000000)
                         || ((ReadAddress & 0x1FF00000) == 0x05A00000)
                         || ((ReadAddress & 0x1DF00000) == 0x05C00000);

      if ((WriteAddress & 0x1FFFFFFF) >= 0x5A00000
            && (WriteAddress & 0x1FFFFFFF) < 0x5FF0000) {
         // Fill a 32-bit value in 16-bit units.  We have to be careful to
         // avoid misaligned 32-bit accesses, because some hardware (e.g.
         // PSP) crashes on such accesses.
         if (constant_source) {
            u32 counter = 0;
            u32 val;
            if (ReadAddress & 2) {  // Avoid misaligned access
               val = MappedMemoryReadWord(ReadAddress) << 16
                   | MappedMemoryReadWord(ReadAddress+2);
            } else {
               val = MappedMemoryReadLong(ReadAddress);
            }
            while (counter < TransferSize) {
               MappedMemoryWriteWord(WriteAddress, (u16)(val >> 16));
               WriteAddress += WriteAdd;
               MappedMemoryWriteWord(WriteAddress, (u16)val);
               WriteAddress += WriteAdd;
               counter += 4;
            }
         } else {
            u32 counter = 0;
            while (counter < TransferSize) {
               u32 tmp = MappedMemoryReadLong(ReadAddress);
               MappedMemoryWriteWord(WriteAddress, (u16)(tmp >> 16));
               WriteAddress += WriteAdd;
               MappedMemoryWriteWord(WriteAddress, (u16)tmp);
               WriteAddress += WriteAdd;
               ReadAddress += ReadAdd;
               counter += 4;
            }
         }
      }
      else {
         // Fill in 32-bit units (always aligned).
         u32 start = WriteAddress;
         if (constant_source) {
            u32 val = MappedMemoryReadLong(ReadAddress);
            u32 counter = 0;
            while (counter < TransferSize) {
               MappedMemoryWriteLong(WriteAddress, val);
               ReadAddress += ReadAdd;
               WriteAddress += WriteAdd;
               counter += 4;
            }
         } else {
            u32 counter = 0;
            while (counter < TransferSize) {
               MappedMemoryWriteLong(WriteAddress,
                                     MappedMemoryReadLong(ReadAddress));
               ReadAddress += ReadAdd;
               WriteAddress += WriteAdd;
               counter += 4;
            }
         }
         // Inform the SH-2 core in case it was a write to main RAM.
         SH2WriteNotify(start, WriteAddress - start);
      }

   }

   else {
      // DMA copy

#ifdef OPTIMIZED_DMA
      int source_type = DMAMemoryType[(ReadAddress  & 0x1FF80000) >> 19];
      int dest_type   = DMAMemoryType[(WriteAddress & 0x1FF80000) >> 19];
      if (WriteAdd == ((dest_type & 0x2) ? 2 : 4)) {
         // Writes don't skip any bytes, so use an optimized copy algorithm
         // if possible.
         const u8 *source_ptr = DMAMemoryPointer(ReadAddress);
         u8 *dest_ptr = DMAMemoryPointer(WriteAddress);
# ifdef WORDS_BIGENDIAN
         if ((source_type & 0x30) && (dest_type & 0x30)) {
            // Source and destination are both directly accessible.
            memcpy(dest_ptr, source_ptr, TransferSize);
            if (dest_type == 0x24) {
               SH2WriteNotify(WriteAddress, TransferSize);
            } else if (dest_type == 0x22) {
               M68KWriteNotify(WriteAddress & 0x7FFFF, TransferSize);
            }
            return;
         }
# else  // !WORDS_BIGENDIAN
         if (source_type & dest_type & 0x10) {
            // Source and destination are both 8-bit organized.
            memcpy(dest_ptr, source_ptr, TransferSize);
            return;
         }
         else if (source_type & dest_type & 0x20) {
            // Source and destination are both 16-bit organized.
            memcpy(dest_ptr, source_ptr, TransferSize);
            if (dest_type == 0x24) {
               SH2WriteNotify(WriteAddress, TransferSize);
            } else if (dest_type == 0x22) {
               M68KWriteNotify(WriteAddress & 0x7FFFF, TransferSize);
            }
            return;
         }
         else if ((source_type | dest_type) >> 4 == 0x3) {
            // Need to convert between 8-bit and 16-bit organization.
            if ((ReadAddress | WriteAddress) & 2) {  // Avoid misaligned access
               const u16 *source_16 = (u16 *)source_ptr;
               u16 *dest_16 = (u16 *)dest_ptr;
               u32 counter;
               for (counter = 0; counter < TransferSize-6;
                     counter += 8, source_16 += 4, dest_16 += 4) {
                  // Use "unsigned int" rather than "u16" because some
                  // compilers try too hard to keep the high bits zero,
                  // thus wasting cycles on every iteration.
                  unsigned int val0 = BSWAP16(source_16[0]);
                  unsigned int val1 = BSWAP16(source_16[1]);
                  unsigned int val2 = BSWAP16(source_16[2]);
                  unsigned int val3 = BSWAP16(source_16[3]);
                  dest_16[0] = val0;
                  dest_16[1] = val1;
                  dest_16[2] = val2;
                  dest_16[3] = val3;
               }
               for (; counter < TransferSize;
                     counter += 2, source_16++, dest_16++) {
                  *dest_16 = BSWAP16(*source_16);
               }
            }
            else {  // 32-bit aligned accesses possible
               const u32 *source_32 = (u32 *)source_ptr;
               u32 *dest_32 = (u32 *)dest_ptr;
               u32 counter;
               for (counter = 0; counter < TransferSize-12;
                     counter += 16, source_32 += 4, dest_32 += 4) {
                  u32 val0 = BSWAP16(source_32[0]);
                  u32 val1 = BSWAP16(source_32[1]);
                  u32 val2 = BSWAP16(source_32[2]);
                  u32 val3 = BSWAP16(source_32[3]);
                  dest_32[0] = val0;
                  dest_32[1] = val1;
                  dest_32[2] = val2;
                  dest_32[3] = val3;
               }
               for (; counter < TransferSize;
                     counter += 4, source_32++, dest_32++) {
                  *dest_32 = BSWAP16(*source_32);
               }
            }
            return;
         }
# endif  // WORDS_BIGENDIAN
      }
#endif  // OPTIMIZED_DMA

      if ((WriteAddress & 0x1FFFFFFF) >= 0x5A00000
          && (WriteAddress & 0x1FFFFFFF) < 0x5FF0000) {
         // Copy in 16-bit units, avoiding misaligned accesses.
         u32 counter = 0;
         if (ReadAddress & 2) {  // Avoid misaligned access
            u16 tmp = MappedMemoryReadWord(ReadAddress);
            MappedMemoryWriteWord(WriteAddress, tmp);
            WriteAddress += WriteAdd;
            ReadAddress += 2;
            counter += 2;
         }
         if (TransferSize >= 3)
         {
            while (counter < TransferSize-2) {
               u32 tmp = MappedMemoryReadLong(ReadAddress);
               MappedMemoryWriteWord(WriteAddress, (u16)(tmp >> 16));
               WriteAddress += WriteAdd;
               MappedMemoryWriteWord(WriteAddress, (u16)tmp);
               WriteAddress += WriteAdd;
               ReadAddress += 4;
               counter += 4;
            }
         }
         if (counter < TransferSize) {
            u16 tmp = MappedMemoryReadWord(ReadAddress);
            MappedMemoryWriteWord(WriteAddress, tmp);
            WriteAddress += WriteAdd;
            ReadAddress += 2;
            counter += 2;
         }
      }
      else {
         u32 counter = 0;
         u32 start = WriteAddress;
         while (counter < TransferSize) {
            MappedMemoryWriteLong(WriteAddress, MappedMemoryReadLong(ReadAddress));
            ReadAddress += 4;
            WriteAddress += WriteAdd;
            counter += 4;
         }
         /* Inform the SH-2 core in case it was a write to main RAM */
         SH2WriteNotify(start, WriteAddress - start);
      }

   }  // Fill / copy
}