#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_target ;
typedef  int bfd_size_type ;
typedef  scalar_t__ bfd_byte ;
struct TYPE_10__ {int /*<<< orphan*/  const* xvec; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 unsigned int AMD64MAGIC ; 
 unsigned int ARMPEMAGIC ; 
 unsigned int H_GET_16 (TYPE_1__*,scalar_t__*) ; 
 int H_GET_32 (TYPE_1__*,scalar_t__*) ; 
 unsigned int I386MAGIC ; 
#define  IMAGE_FILE_MACHINE_ALPHA 145 
#define  IMAGE_FILE_MACHINE_ALPHA64 144 
#define  IMAGE_FILE_MACHINE_AMD64 143 
#define  IMAGE_FILE_MACHINE_ARM 142 
#define  IMAGE_FILE_MACHINE_I386 141 
#define  IMAGE_FILE_MACHINE_IA64 140 
#define  IMAGE_FILE_MACHINE_M68K 139 
#define  IMAGE_FILE_MACHINE_MIPS16 138 
#define  IMAGE_FILE_MACHINE_MIPSFPU 137 
#define  IMAGE_FILE_MACHINE_MIPSFPU16 136 
#define  IMAGE_FILE_MACHINE_POWERPC 135 
#define  IMAGE_FILE_MACHINE_R10000 134 
#define  IMAGE_FILE_MACHINE_R3000 133 
#define  IMAGE_FILE_MACHINE_R4000 132 
#define  IMAGE_FILE_MACHINE_SH3 131 
#define  IMAGE_FILE_MACHINE_SH4 130 
#define  IMAGE_FILE_MACHINE_THUMB 129 
#define  IMAGE_FILE_MACHINE_UNKNOWN 128 
 unsigned int MC68MAGIC ; 
 unsigned int MIPS_ARCH_MAGIC_WINCE ; 
 unsigned int SH_ARCH_MAGIC_WINCE ; 
 unsigned int THUMBPEMAGIC ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,TYPE_1__*,...) ; 
 scalar_t__* bfd_alloc (TYPE_1__*,int) ; 
 int bfd_bread (scalar_t__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_error_malformed_archive ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int /*<<< orphan*/  bfd_release (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_ILF_build_a_bfd (TYPE_1__*,unsigned int,char*,char*,unsigned int,unsigned int) ; 
 int strlen (char*) ; 

__attribute__((used)) static const bfd_target *
pe_ILF_object_p (bfd * abfd)
{
  bfd_byte        buffer[16];
  bfd_byte *      ptr;
  char *          symbol_name;
  char *          source_dll;
  unsigned int    machine;
  bfd_size_type   size;
  unsigned int    ordinal;
  unsigned int    types;
  unsigned int    magic;

  /* Upon entry the first four buyes of the ILF header have
      already been read.  Now read the rest of the header.  */
  if (bfd_bread (buffer, (bfd_size_type) 16, abfd) != 16)
    return NULL;

  ptr = buffer;

  /*  We do not bother to check the version number.
      version = H_GET_16 (abfd, ptr);  */
  ptr += 2;

  machine = H_GET_16 (abfd, ptr);
  ptr += 2;

  /* Check that the machine type is recognised.  */
  magic = 0;

  switch (machine)
    {
    case IMAGE_FILE_MACHINE_UNKNOWN:
    case IMAGE_FILE_MACHINE_ALPHA:
    case IMAGE_FILE_MACHINE_ALPHA64:
    case IMAGE_FILE_MACHINE_IA64:
      break;

    case IMAGE_FILE_MACHINE_I386:
#ifdef I386MAGIC
      magic = I386MAGIC;
#endif
      break;

    case IMAGE_FILE_MACHINE_AMD64:
#ifdef AMD64MAGIC
      magic = AMD64MAGIC;
#endif
      break;

    case IMAGE_FILE_MACHINE_M68K:
#ifdef MC68AGIC
      magic = MC68MAGIC;
#endif
      break;

    case IMAGE_FILE_MACHINE_R3000:
    case IMAGE_FILE_MACHINE_R4000:
    case IMAGE_FILE_MACHINE_R10000:

    case IMAGE_FILE_MACHINE_MIPS16:
    case IMAGE_FILE_MACHINE_MIPSFPU:
    case IMAGE_FILE_MACHINE_MIPSFPU16:
#ifdef MIPS_ARCH_MAGIC_WINCE
      magic = MIPS_ARCH_MAGIC_WINCE;
#endif
      break;

    case IMAGE_FILE_MACHINE_SH3:
    case IMAGE_FILE_MACHINE_SH4:
#ifdef SH_ARCH_MAGIC_WINCE
      magic = SH_ARCH_MAGIC_WINCE;
#endif
      break;

    case IMAGE_FILE_MACHINE_ARM:
#ifdef ARMPEMAGIC
      magic = ARMPEMAGIC;
#endif
      break;

    case IMAGE_FILE_MACHINE_THUMB:
#ifdef THUMBPEMAGIC
      {
	extern const bfd_target TARGET_LITTLE_SYM;

	if (abfd->xvec == & TARGET_LITTLE_SYM)
	  magic = THUMBPEMAGIC;
      }
#endif
      break;

    case IMAGE_FILE_MACHINE_POWERPC:
      /* We no longer support PowerPC.  */
    default:
      _bfd_error_handler
	(_("%B: Unrecognised machine type (0x%x)"
	   " in Import Library Format archive"),
	 abfd, machine);
      bfd_set_error (bfd_error_malformed_archive);

      return NULL;
      break;
    }

  if (magic == 0)
    {
      _bfd_error_handler
	(_("%B: Recognised but unhandled machine type (0x%x)"
	   " in Import Library Format archive"),
	 abfd, machine);
      bfd_set_error (bfd_error_wrong_format);

      return NULL;
    }

  /* We do not bother to check the date.
     date = H_GET_32 (abfd, ptr);  */
  ptr += 4;

  size = H_GET_32 (abfd, ptr);
  ptr += 4;

  if (size == 0)
    {
      _bfd_error_handler
	(_("%B: size field is zero in Import Library Format header"), abfd);
      bfd_set_error (bfd_error_malformed_archive);

      return NULL;
    }

  ordinal = H_GET_16 (abfd, ptr);
  ptr += 2;

  types = H_GET_16 (abfd, ptr);
  /* ptr += 2; */

  /* Now read in the two strings that follow.  */
  ptr = bfd_alloc (abfd, size);
  if (ptr == NULL)
    return NULL;

  if (bfd_bread (ptr, size, abfd) != size)
    {
      bfd_release (abfd, ptr);
      return NULL;
    }

  symbol_name = (char *) ptr;
  source_dll  = symbol_name + strlen (symbol_name) + 1;

  /* Verify that the strings are null terminated.  */
  if (ptr[size - 1] != 0
      || (bfd_size_type) ((bfd_byte *) source_dll - ptr) >= size)
    {
      _bfd_error_handler
	(_("%B: string not null terminated in ILF object file."), abfd);
      bfd_set_error (bfd_error_malformed_archive);
      bfd_release (abfd, ptr);
      return NULL;
    }

  /* Now construct the bfd.  */
  if (! pe_ILF_build_a_bfd (abfd, magic, symbol_name,
			    source_dll, ordinal, types))
    {
      bfd_release (abfd, ptr);
      return NULL;
    }

  return abfd->xvec;
}