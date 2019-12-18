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
struct TYPE_2__ {unsigned int* prefix; int /*<<< orphan*/  prefixes; } ;

/* Variables and functions */
 unsigned int ADDR_PREFIX ; 
#define  ADDR_PREFIX_OPCODE 139 
 scalar_t__ CODE_64BIT ; 
#define  CS_PREFIX_OPCODE 138 
 unsigned int DATA_PREFIX ; 
#define  DATA_PREFIX_OPCODE 137 
#define  DS_PREFIX_OPCODE 136 
#define  ES_PREFIX_OPCODE 135 
#define  FS_PREFIX_OPCODE 134 
#define  FWAIT_OPCODE 133 
#define  GS_PREFIX_OPCODE 132 
 unsigned int LOCKREP_PREFIX ; 
#define  LOCK_PREFIX_OPCODE 131 
#define  REPE_PREFIX_OPCODE 130 
#define  REPNE_PREFIX_OPCODE 129 
 unsigned int REX_B ; 
 unsigned int REX_OPCODE ; 
 size_t REX_PREFIX ; 
 unsigned int REX_R ; 
 unsigned int REX_W ; 
 unsigned int REX_X ; 
 unsigned int SEG_PREFIX ; 
#define  SS_PREFIX_OPCODE 128 
 unsigned int WAIT_PREFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_code ; 
 TYPE_1__ i ; 

__attribute__((used)) static int
add_prefix (unsigned int prefix)
{
  int ret = 1;
  unsigned int q;

  if (prefix >= REX_OPCODE && prefix < REX_OPCODE + 16
      && flag_code == CODE_64BIT)
    {
      if ((i.prefix[REX_PREFIX] & prefix & REX_W)
	  || ((i.prefix[REX_PREFIX] & (REX_R | REX_X | REX_B))
	      && (prefix & (REX_R | REX_X | REX_B))))
	ret = 0;
      q = REX_PREFIX;
    }
  else
    {
      switch (prefix)
	{
	default:
	  abort ();

	case CS_PREFIX_OPCODE:
	case DS_PREFIX_OPCODE:
	case ES_PREFIX_OPCODE:
	case FS_PREFIX_OPCODE:
	case GS_PREFIX_OPCODE:
	case SS_PREFIX_OPCODE:
	  q = SEG_PREFIX;
	  break;

	case REPNE_PREFIX_OPCODE:
	case REPE_PREFIX_OPCODE:
	  ret = 2;
	  /* fall thru */
	case LOCK_PREFIX_OPCODE:
	  q = LOCKREP_PREFIX;
	  break;

	case FWAIT_OPCODE:
	  q = WAIT_PREFIX;
	  break;

	case ADDR_PREFIX_OPCODE:
	  q = ADDR_PREFIX;
	  break;

	case DATA_PREFIX_OPCODE:
	  q = DATA_PREFIX;
	  break;
	}
      if (i.prefix[q] != 0)
	ret = 0;
    }

  if (ret)
    {
      if (!i.prefix[q])
	++i.prefixes;
      i.prefix[q] |= prefix;
    }
  else
    as_bad (_("same type of prefix used twice"));

  return ret;
}