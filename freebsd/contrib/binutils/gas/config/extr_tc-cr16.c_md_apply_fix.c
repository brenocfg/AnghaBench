#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ valueT ;
typedef  scalar_t__ segT ;
struct TYPE_5__ {int fx_where; int fx_r_type; int fx_done; int fx_pcrel; int /*<<< orphan*/ * fx_addsy; scalar_t__ fx_offset; TYPE_1__* fx_frag; } ;
typedef  TYPE_2__ fixS ;
struct TYPE_4__ {char* fr_literal; } ;

/* Variables and functions */
#define  BFD_RELOC_CR16_NUM16 131 
#define  BFD_RELOC_CR16_NUM32 130 
#define  BFD_RELOC_CR16_NUM32a 129 
#define  BFD_RELOC_CR16_NUM8 128 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_put_16 (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  bfd_put_8 (int /*<<< orphan*/ ,unsigned char,char*) ; 
 int /*<<< orphan*/  stdoutput ; 

void
md_apply_fix (fixS *fixP, valueT *valP, segT seg)
{
  valueT val = * valP;
  char *buf = fixP->fx_frag->fr_literal + fixP->fx_where;
  fixP->fx_offset = 0;

  switch (fixP->fx_r_type)
    {
      case BFD_RELOC_CR16_NUM8:
        bfd_put_8 (stdoutput, (unsigned char) val, buf);
        break;
      case BFD_RELOC_CR16_NUM16:
        bfd_put_16 (stdoutput, val, buf);
        break;
      case BFD_RELOC_CR16_NUM32:
        bfd_put_32 (stdoutput, val, buf);
        break;
      case BFD_RELOC_CR16_NUM32a:
        bfd_put_32 (stdoutput, val, buf);
        break;
      default:
        /* We shouldn't ever get here because linkrelax is nonzero.  */
        abort ();
        break;
    }

  fixP->fx_done = 0;

  if (fixP->fx_addsy == NULL
      && fixP->fx_pcrel == 0)
    fixP->fx_done = 1;

  if (fixP->fx_pcrel == 1
      && fixP->fx_addsy != NULL
      && S_GET_SEGMENT (fixP->fx_addsy) == seg)
    fixP->fx_done = 1;
}