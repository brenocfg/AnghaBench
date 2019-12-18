#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int Z80PC; int Z80PC_BASE; int Z80SP; int Z80SP_BASE; } ;

/* Variables and functions */
 int /*<<< orphan*/  BasePC ; 
 TYPE_1__ CZ80 ; 
 int /*<<< orphan*/  CZ80_PC ; 
 int /*<<< orphan*/  Cz80_Set_Reg (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cz80_struc ; 
 TYPE_1__ drZ80 ; 
 int /*<<< orphan*/  drz80_load_pcsp (int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,void const*,int) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int z80_unpack_legacy(const void *data)
{
#if defined(_USE_DRZ80)
  if (*(int *)data == 0x015A7244) { // "DrZ" v1 save?
    u32 pc, sp;
    memcpy(&drZ80, data+4, 0x54);
    pc = (drZ80.Z80PC - drZ80.Z80PC_BASE) & 0xffff;
    sp = (drZ80.Z80SP - drZ80.Z80SP_BASE) & 0xffff;
    // update bases
    drz80_load_pcsp(pc, sp);
    return 0;
  }
#elif defined(_USE_CZ80)
  if (*(int *)data == 0x00007a43) { // "Cz" save?
    memcpy(&CZ80, data+8, offsetof(cz80_struc, BasePC));
    Cz80_Set_Reg(&CZ80, CZ80_PC, *(int *)(data+4));
    return 0;
  }
#endif
  return -1;
}