#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * Cs0WriteLong; int /*<<< orphan*/ * Cs0WriteWord; int /*<<< orphan*/ * Cs0WriteByte; int /*<<< orphan*/ * Cs0ReadLong; int /*<<< orphan*/ * Cs0ReadWord; int /*<<< orphan*/ * Cs0ReadByte; } ;

/* Variables and functions */
 int /*<<< orphan*/  BiosRomMemoryReadByte ; 
 int /*<<< orphan*/  BiosRomMemoryReadLong ; 
 int /*<<< orphan*/  BiosRomMemoryReadWord ; 
 int /*<<< orphan*/  BiosRomMemoryWriteByte ; 
 int /*<<< orphan*/  BiosRomMemoryWriteLong ; 
 int /*<<< orphan*/  BiosRomMemoryWriteWord ; 
 int /*<<< orphan*/  BupRamMemoryReadByte ; 
 int /*<<< orphan*/  BupRamMemoryReadLong ; 
 int /*<<< orphan*/  BupRamMemoryReadWord ; 
 int /*<<< orphan*/  BupRamMemoryWriteByte ; 
 int /*<<< orphan*/  BupRamMemoryWriteLong ; 
 int /*<<< orphan*/  BupRamMemoryWriteWord ; 
 TYPE_1__* CartridgeArea ; 
 int /*<<< orphan*/  Cs1ReadByte ; 
 int /*<<< orphan*/  Cs1ReadLong ; 
 int /*<<< orphan*/  Cs1ReadWord ; 
 int /*<<< orphan*/  Cs1WriteByte ; 
 int /*<<< orphan*/  Cs1WriteLong ; 
 int /*<<< orphan*/  Cs1WriteWord ; 
 int /*<<< orphan*/  Cs2ReadByte ; 
 int /*<<< orphan*/  Cs2ReadLong ; 
 int /*<<< orphan*/  Cs2ReadWord ; 
 int /*<<< orphan*/  Cs2WriteByte ; 
 int /*<<< orphan*/  Cs2WriteLong ; 
 int /*<<< orphan*/  Cs2WriteWord ; 
 int /*<<< orphan*/  FillMemoryArea (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HighWramMemoryReadByte ; 
 int /*<<< orphan*/  HighWramMemoryReadLong ; 
 int /*<<< orphan*/  HighWramMemoryReadWord ; 
 int /*<<< orphan*/  HighWramMemoryWriteByte ; 
 int /*<<< orphan*/  HighWramMemoryWriteLong ; 
 int /*<<< orphan*/  HighWramMemoryWriteWord ; 
 int /*<<< orphan*/  LowWramMemoryReadByte ; 
 int /*<<< orphan*/  LowWramMemoryReadLong ; 
 int /*<<< orphan*/  LowWramMemoryReadWord ; 
 int /*<<< orphan*/  LowWramMemoryWriteByte ; 
 int /*<<< orphan*/  LowWramMemoryWriteLong ; 
 int /*<<< orphan*/  LowWramMemoryWriteWord ; 
 int /*<<< orphan*/  MSH2InputCaptureWriteWord ; 
 int /*<<< orphan*/  SSH2InputCaptureWriteWord ; 
 int /*<<< orphan*/  ScuReadByte ; 
 int /*<<< orphan*/  ScuReadLong ; 
 int /*<<< orphan*/  ScuReadWord ; 
 int /*<<< orphan*/  ScuWriteByte ; 
 int /*<<< orphan*/  ScuWriteLong ; 
 int /*<<< orphan*/  ScuWriteWord ; 
 int /*<<< orphan*/  SmpcReadByte ; 
 int /*<<< orphan*/  SmpcReadLong ; 
 int /*<<< orphan*/  SmpcReadWord ; 
 int /*<<< orphan*/  SmpcWriteByte ; 
 int /*<<< orphan*/  SmpcWriteLong ; 
 int /*<<< orphan*/  SmpcWriteWord ; 
 int /*<<< orphan*/  SoundRamReadByte ; 
 int /*<<< orphan*/  SoundRamReadLong ; 
 int /*<<< orphan*/  SoundRamReadWord ; 
 int /*<<< orphan*/  SoundRamWriteByte ; 
 int /*<<< orphan*/  SoundRamWriteLong ; 
 int /*<<< orphan*/  SoundRamWriteWord ; 
 int /*<<< orphan*/  UnhandledMemoryReadByte ; 
 int /*<<< orphan*/  UnhandledMemoryReadLong ; 
 int /*<<< orphan*/  UnhandledMemoryReadWord ; 
 int /*<<< orphan*/  UnhandledMemoryWriteByte ; 
 int /*<<< orphan*/  UnhandledMemoryWriteLong ; 
 int /*<<< orphan*/  UnhandledMemoryWriteWord ; 
 int /*<<< orphan*/  Vdp1FrameBufferReadByte ; 
 int /*<<< orphan*/  Vdp1FrameBufferReadLong ; 
 int /*<<< orphan*/  Vdp1FrameBufferReadWord ; 
 int /*<<< orphan*/  Vdp1FrameBufferWriteByte ; 
 int /*<<< orphan*/  Vdp1FrameBufferWriteLong ; 
 int /*<<< orphan*/  Vdp1FrameBufferWriteWord ; 
 int /*<<< orphan*/  Vdp1RamReadByte ; 
 int /*<<< orphan*/  Vdp1RamReadLong ; 
 int /*<<< orphan*/  Vdp1RamReadWord ; 
 int /*<<< orphan*/  Vdp1RamWriteByte ; 
 int /*<<< orphan*/  Vdp1RamWriteLong ; 
 int /*<<< orphan*/  Vdp1RamWriteWord ; 
 int /*<<< orphan*/  Vdp1ReadByte ; 
 int /*<<< orphan*/  Vdp1ReadLong ; 
 int /*<<< orphan*/  Vdp1ReadWord ; 
 int /*<<< orphan*/  Vdp1WriteByte ; 
 int /*<<< orphan*/  Vdp1WriteLong ; 
 int /*<<< orphan*/  Vdp1WriteWord ; 
 int /*<<< orphan*/  Vdp2ColorRamReadByte ; 
 int /*<<< orphan*/  Vdp2ColorRamReadLong ; 
 int /*<<< orphan*/  Vdp2ColorRamReadWord ; 
 int /*<<< orphan*/  Vdp2ColorRamWriteByte ; 
 int /*<<< orphan*/  Vdp2ColorRamWriteLong ; 
 int /*<<< orphan*/  Vdp2ColorRamWriteWord ; 
 int /*<<< orphan*/  Vdp2RamReadByte ; 
 int /*<<< orphan*/  Vdp2RamReadLong ; 
 int /*<<< orphan*/  Vdp2RamReadWord ; 
 int /*<<< orphan*/  Vdp2RamWriteByte ; 
 int /*<<< orphan*/  Vdp2RamWriteLong ; 
 int /*<<< orphan*/  Vdp2RamWriteWord ; 
 int /*<<< orphan*/  Vdp2ReadByte ; 
 int /*<<< orphan*/  Vdp2ReadLong ; 
 int /*<<< orphan*/  Vdp2ReadWord ; 
 int /*<<< orphan*/  Vdp2WriteByte ; 
 int /*<<< orphan*/  Vdp2WriteLong ; 
 int /*<<< orphan*/  Vdp2WriteWord ; 
 int /*<<< orphan*/  scsp_r_b ; 
 int /*<<< orphan*/  scsp_r_d ; 
 int /*<<< orphan*/  scsp_r_w ; 
 int /*<<< orphan*/  scsp_w_b ; 
 int /*<<< orphan*/  scsp_w_d ; 
 int /*<<< orphan*/  scsp_w_w ; 

void MappedMemoryInit()
{
   // Initialize everyting to unhandled to begin with
   FillMemoryArea(0x000, 0xFFF, &UnhandledMemoryReadByte,
                                &UnhandledMemoryReadWord,
                                &UnhandledMemoryReadLong,
                                &UnhandledMemoryWriteByte,
                                &UnhandledMemoryWriteWord,
                                &UnhandledMemoryWriteLong);

   // Fill the rest
   FillMemoryArea(0x000, 0x00F, &BiosRomMemoryReadByte,
                                &BiosRomMemoryReadWord,
                                &BiosRomMemoryReadLong,
                                &BiosRomMemoryWriteByte,
                                &BiosRomMemoryWriteWord,
                                &BiosRomMemoryWriteLong);
   FillMemoryArea(0x010, 0x017, &SmpcReadByte,
                                &SmpcReadWord,
                                &SmpcReadLong,
                                &SmpcWriteByte,
                                &SmpcWriteWord,
                                &SmpcWriteLong);
   FillMemoryArea(0x018, 0x01F, &BupRamMemoryReadByte,
                                &BupRamMemoryReadWord,
                                &BupRamMemoryReadLong,
                                &BupRamMemoryWriteByte,
                                &BupRamMemoryWriteWord,
                                &BupRamMemoryWriteLong);
   FillMemoryArea(0x020, 0x02F, &LowWramMemoryReadByte,
                                &LowWramMemoryReadWord,
                                &LowWramMemoryReadLong,
                                &LowWramMemoryWriteByte,
                                &LowWramMemoryWriteWord,
                                &LowWramMemoryWriteLong);
   FillMemoryArea(0x100, 0x17F, &UnhandledMemoryReadByte,
                                &UnhandledMemoryReadWord,
                                &UnhandledMemoryReadLong,
                                &UnhandledMemoryWriteByte,
                                &SSH2InputCaptureWriteWord,
                                &UnhandledMemoryWriteLong);
   FillMemoryArea(0x180, 0x1FF, &UnhandledMemoryReadByte,
                                &UnhandledMemoryReadWord,
                                &UnhandledMemoryReadLong,
                                &UnhandledMemoryWriteByte,
                                &MSH2InputCaptureWriteWord,
                                &UnhandledMemoryWriteLong);
   FillMemoryArea(0x200, 0x3FF, CartridgeArea->Cs0ReadByte,
                                CartridgeArea->Cs0ReadWord,
                                CartridgeArea->Cs0ReadLong,
                                CartridgeArea->Cs0WriteByte,
                                CartridgeArea->Cs0WriteWord,
                                CartridgeArea->Cs0WriteLong);
   FillMemoryArea(0x400, 0x4FF, &Cs1ReadByte,
                                &Cs1ReadWord,
                                &Cs1ReadLong,
                                &Cs1WriteByte,
                                &Cs1WriteWord,
                                &Cs1WriteLong);
   FillMemoryArea(0x580, 0x58F, &Cs2ReadByte,
                                &Cs2ReadWord,
                                &Cs2ReadLong,
                                &Cs2WriteByte,
                                &Cs2WriteWord,
                                &Cs2WriteLong);
   FillMemoryArea(0x5A0, 0x5AF, &SoundRamReadByte,
                                &SoundRamReadWord,
                                &SoundRamReadLong,
                                &SoundRamWriteByte,
                                &SoundRamWriteWord,
                                &SoundRamWriteLong);
   FillMemoryArea(0x5B0, 0x5BF, &scsp_r_b,
                                &scsp_r_w,
                                &scsp_r_d,
                                &scsp_w_b,
                                &scsp_w_w,
                                &scsp_w_d);
   FillMemoryArea(0x5C0, 0x5C7, &Vdp1RamReadByte,
                                &Vdp1RamReadWord,
                                &Vdp1RamReadLong,
                                &Vdp1RamWriteByte,
                                &Vdp1RamWriteWord,
                                &Vdp1RamWriteLong);
   FillMemoryArea(0x5C8, 0x5CF, &Vdp1FrameBufferReadByte,
                                &Vdp1FrameBufferReadWord,
                                &Vdp1FrameBufferReadLong,
                                &Vdp1FrameBufferWriteByte,
                                &Vdp1FrameBufferWriteWord,
                                &Vdp1FrameBufferWriteLong);
   FillMemoryArea(0x5D0, 0x5D7, &Vdp1ReadByte,
                                &Vdp1ReadWord,
                                &Vdp1ReadLong,
                                &Vdp1WriteByte,
                                &Vdp1WriteWord,
                                &Vdp1WriteLong);
   FillMemoryArea(0x5E0, 0x5EF, &Vdp2RamReadByte,
                                &Vdp2RamReadWord,
                                &Vdp2RamReadLong,
                                &Vdp2RamWriteByte,
                                &Vdp2RamWriteWord,
                                &Vdp2RamWriteLong);
   FillMemoryArea(0x5F0, 0x5F7, &Vdp2ColorRamReadByte,
                                &Vdp2ColorRamReadWord,
                                &Vdp2ColorRamReadLong,
                                &Vdp2ColorRamWriteByte,
                                &Vdp2ColorRamWriteWord,
                                &Vdp2ColorRamWriteLong);
   FillMemoryArea(0x5F8, 0x5FB, &Vdp2ReadByte,
                                &Vdp2ReadWord,
                                &Vdp2ReadLong,
                                &Vdp2WriteByte,
                                &Vdp2WriteWord,
                                &Vdp2WriteLong);
   FillMemoryArea(0x5FE, 0x5FE, &ScuReadByte,
                                &ScuReadWord,
                                &ScuReadLong,
                                &ScuWriteByte,
                                &ScuWriteWord,
                                &ScuWriteLong);
   FillMemoryArea(0x600, 0x7FF, &HighWramMemoryReadByte,
                                &HighWramMemoryReadWord,
                                &HighWramMemoryReadLong,
                                &HighWramMemoryWriteByte,
                                &HighWramMemoryWriteWord,
                                &HighWramMemoryWriteLong);
}