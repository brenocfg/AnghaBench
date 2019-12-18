#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dwarf_cie {unsigned char* augmentation; int version; } ;
struct _Unwind_Context {int dummy; } ;
typedef  int _Unwind_Word ;
typedef  scalar_t__ _Unwind_Ptr ;
typedef  scalar_t__ _Unwind_Personality_Fn ;
struct TYPE_3__ {int code_align; int retaddr_column; int saw_z; int signal_frame; scalar_t__ personality; int /*<<< orphan*/  fde_encoding; int /*<<< orphan*/  lsda_encoding; int /*<<< orphan*/  data_align; int /*<<< orphan*/  eh_ptr; } ;
typedef  TYPE_1__ _Unwind_FrameState ;

/* Variables and functions */
 int /*<<< orphan*/  DW_EH_PE_omit ; 
 unsigned char* read_encoded_value (struct _Unwind_Context*,unsigned char const,unsigned char const*,scalar_t__*) ; 
 int /*<<< orphan*/  read_pointer (unsigned char const*) ; 
 unsigned char* read_sleb128 (unsigned char const*,int /*<<< orphan*/ *) ; 
 unsigned char* read_uleb128 (unsigned char const*,int*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const unsigned char *
extract_cie_info (const struct dwarf_cie *cie, struct _Unwind_Context *context,
		  _Unwind_FrameState *fs)
{
  const unsigned char *aug = cie->augmentation;
  const unsigned char *p = aug + strlen ((const char *)aug) + 1;
  const unsigned char *ret = NULL;
  _Unwind_Word utmp;

  /* g++ v2 "eh" has pointer immediately following augmentation string,
     so it must be handled first.  */
  if (aug[0] == 'e' && aug[1] == 'h')
    {
      fs->eh_ptr = read_pointer (p);
      p += sizeof (void *);
      aug += 2;
    }

  /* Immediately following the augmentation are the code and
     data alignment and return address column.  */
  p = read_uleb128 (p, &fs->code_align);
  p = read_sleb128 (p, &fs->data_align);
  if (cie->version == 1)
    fs->retaddr_column = *p++;
  else
    p = read_uleb128 (p, &fs->retaddr_column);
  fs->lsda_encoding = DW_EH_PE_omit;

  /* If the augmentation starts with 'z', then a uleb128 immediately
     follows containing the length of the augmentation field following
     the size.  */
  if (*aug == 'z')
    {
      p = read_uleb128 (p, &utmp);
      ret = p + utmp;

      fs->saw_z = 1;
      ++aug;
    }

  /* Iterate over recognized augmentation subsequences.  */
  while (*aug != '\0')
    {
      /* "L" indicates a byte showing how the LSDA pointer is encoded.  */
      if (aug[0] == 'L')
	{
	  fs->lsda_encoding = *p++;
	  aug += 1;
	}

      /* "R" indicates a byte indicating how FDE addresses are encoded.  */
      else if (aug[0] == 'R')
	{
	  fs->fde_encoding = *p++;
	  aug += 1;
	}

      /* "P" indicates a personality routine in the CIE augmentation.  */
      else if (aug[0] == 'P')
	{
	  _Unwind_Ptr personality;
	  
	  p = read_encoded_value (context, *p, p + 1, &personality);
	  fs->personality = (_Unwind_Personality_Fn) personality;
	  aug += 1;
	}

      /* "S" indicates a signal frame.  */
      else if (aug[0] == 'S')
	{
	  fs->signal_frame = 1;
	  aug += 1;
	}

      /* Otherwise we have an unknown augmentation string.
	 Bail unless we saw a 'z' prefix.  */
      else
	return ret;
    }

  return ret ? ret : p;
}