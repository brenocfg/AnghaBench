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
#define  R_ALPHA_GOTDTPREL 135 
#define  R_ALPHA_GOTTPREL 134 
#define  R_ALPHA_LITERAL 133 
#define  R_ALPHA_REFLONG 132 
#define  R_ALPHA_REFQUAD 131 
#define  R_ALPHA_TLSGD 130 
#define  R_ALPHA_TLSLDM 129 
#define  R_ALPHA_TPREL64 128 

__attribute__((used)) static int
alpha_dynamic_entries_for_reloc (int r_type, int dynamic, int shared)
{
  switch (r_type)
    {
    /* May appear in GOT entries.  */
    case R_ALPHA_TLSGD:
      return (dynamic ? 2 : shared ? 1 : 0);
    case R_ALPHA_TLSLDM:
      return shared;
    case R_ALPHA_LITERAL:
    case R_ALPHA_GOTTPREL:
      return dynamic || shared;
    case R_ALPHA_GOTDTPREL:
      return dynamic;

    /* May appear in data sections.  */
    case R_ALPHA_REFLONG:
    case R_ALPHA_REFQUAD:
    case R_ALPHA_TPREL64:
      return dynamic || shared;

    /* Everything else is illegal.  We'll issue an error during
       relocate_section.  */
    default:
      return 0;
    }
}