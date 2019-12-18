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

/* Variables and functions */
#define  DW_EH_PE_absptr 131 
 unsigned char DW_EH_PE_omit ; 
#define  DW_EH_PE_udata2 130 
#define  DW_EH_PE_udata4 129 
#define  DW_EH_PE_udata8 128 
 int /*<<< orphan*/  __gxx_abort () ; 

__attribute__((used)) static unsigned int
size_of_encoded_value (unsigned char encoding)
{
  if (encoding == DW_EH_PE_omit)
    return 0;

  switch (encoding & 0x07)
    {
    case DW_EH_PE_absptr:
      return sizeof (void *);
    case DW_EH_PE_udata2:
      return 2;
    case DW_EH_PE_udata4:
      return 4;
    case DW_EH_PE_udata8:
      return 8;
    }
  __gxx_abort ();
}