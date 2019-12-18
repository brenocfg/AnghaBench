#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_21__ {int /*<<< orphan*/  l; int /*<<< orphan*/  h; int /*<<< orphan*/  e; int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  f; int /*<<< orphan*/  a; } ;
struct TYPE_14__ {int /*<<< orphan*/  l; int /*<<< orphan*/  h; int /*<<< orphan*/  e; int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  f; int /*<<< orphan*/  a; } ;
struct z80_state {int* irq_vector; scalar_t__ irq_pending; int /*<<< orphan*/  im; scalar_t__ iff2; scalar_t__ iff1; scalar_t__ halted; scalar_t__ pc; scalar_t__ sp; int /*<<< orphan*/  iy; int /*<<< orphan*/  ix; int /*<<< orphan*/  r; int /*<<< orphan*/  i; TYPE_8__ a; TYPE_1__ m; int /*<<< orphan*/  magic; } ;
struct TYPE_19__ {int /*<<< orphan*/  L; int /*<<< orphan*/  H; } ;
struct TYPE_20__ {TYPE_6__ B; } ;
struct TYPE_17__ {int /*<<< orphan*/  L; int /*<<< orphan*/  H; } ;
struct TYPE_18__ {TYPE_4__ B; } ;
struct TYPE_15__ {int /*<<< orphan*/  L; int /*<<< orphan*/  H; } ;
struct TYPE_16__ {TYPE_2__ B; } ;
struct TYPE_22__ {TYPE_7__ HL2; TYPE_5__ DE2; TYPE_3__ BC2; } ;
typedef  TYPE_9__ cz80_struc ;
struct TYPE_13__ {int Z80IF; int z80irqvector; scalar_t__ Z80_IRQ; int /*<<< orphan*/  Z80IM; int /*<<< orphan*/  spare; int /*<<< orphan*/  Z80F2; int /*<<< orphan*/  Z80F; } ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  A2 ; 
 int /*<<< orphan*/  BC ; 
 int /*<<< orphan*/  BC2 ; 
 scalar_t__ CLEAR_LINE ; 
 TYPE_9__ CZ80 ; 
 int /*<<< orphan*/  CZ80_HALT ; 
 int /*<<< orphan*/  CZ80_IFF1 ; 
 int /*<<< orphan*/  CZ80_IFF2 ; 
 int /*<<< orphan*/  CZ80_IRQ ; 
 int /*<<< orphan*/  CZ80_PC ; 
 int /*<<< orphan*/  CZ80_SP ; 
 int /*<<< orphan*/  Cz80_Set_Reg (TYPE_9__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DE ; 
 int /*<<< orphan*/  DE2 ; 
 int /*<<< orphan*/  DRW16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRW16HL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRW8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EL_ANOMALY ; 
 int EL_STATUS ; 
 int /*<<< orphan*/  HL ; 
 int /*<<< orphan*/  HL2 ; 
 scalar_t__ HOLD_LINE ; 
 int /*<<< orphan*/  I ; 
 int /*<<< orphan*/  IX ; 
 int /*<<< orphan*/  IY ; 
 TYPE_10__ drZ80 ; 
 int /*<<< orphan*/  drz80_load_pcsp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  elprintf (int,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  z80_int () ; 
 int /*<<< orphan*/  z80_reset () ; 
 scalar_t__ z80_unpack_legacy (void const*) ; 
 int /*<<< orphan*/  zA ; 
 int /*<<< orphan*/  zA2 ; 
 int /*<<< orphan*/  zB ; 
 int /*<<< orphan*/  zC ; 
 int /*<<< orphan*/  zD ; 
 int /*<<< orphan*/  zE ; 
 int /*<<< orphan*/  zF ; 
 int /*<<< orphan*/  zF2 ; 
 int /*<<< orphan*/  zH ; 
 int /*<<< orphan*/  zI ; 
 int /*<<< orphan*/  zIM ; 
 int /*<<< orphan*/  zIX ; 
 int /*<<< orphan*/  zIY ; 
 int /*<<< orphan*/  zL ; 
 int /*<<< orphan*/  zR ; 

int z80_unpack(const void *data)
{
  const struct z80_state *s = data;
  if (strcmp(s->magic, "Z80") != 0) {
    if (z80_unpack_legacy(data) != 0)
      goto fail;
    elprintf(EL_STATUS, "legacy z80 state");
    return 0;
  }

#if defined(_USE_DRZ80)
  #define DRW8(n, v)       drZ80.Z80##n = (u32)(v) << 24
  #define DRW16(n, v)      drZ80.Z80##n = (u32)(v) << 16
  #define DRW16HL(n, h, l) drZ80.Z80##n = ((u32)(h) << 24) | ((u32)(l) << 16)
  DRW8(A, s->m.a);  drZ80.Z80F = s->m.f;
  DRW16HL(BC, s->m.b, s->m.c);
  DRW16HL(DE, s->m.d, s->m.e);
  DRW16HL(HL, s->m.h, s->m.l);
  DRW8(A2, s->a.a); drZ80.Z80F2 = s->a.f;
  DRW16HL(BC2, s->a.b, s->a.c);
  DRW16HL(DE2, s->a.d, s->a.e);
  DRW16HL(HL2, s->a.h, s->a.l);
  DRW8(I, s->i);    drZ80.spare = s->r;
  DRW16(IX, s->ix); DRW16(IY, s->iy);
  drz80_load_pcsp(s->pc, s->sp);
  drZ80.Z80IF = 0;
  if (s->halted) drZ80.Z80IF |= 4;
  if (s->iff1)   drZ80.Z80IF |= 1;
  if (s->iff2)   drZ80.Z80IF |= 2;
  drZ80.Z80IM = s->im;
  drZ80.Z80_IRQ = s->irq_pending;
  drZ80.z80irqvector = ((u32)s->irq_vector[0] << 16) |
    ((u32)s->irq_vector[1] << 8) | s->irq_vector[2];
  return 0;
#elif defined(_USE_CZ80)
  {
    cz80_struc *CPU = &CZ80;
    zA  = s->m.a; zF  = s->m.f;
    zB  = s->m.b; zC  = s->m.c;
    zD  = s->m.d; zE  = s->m.e;
    zH  = s->m.h; zL  = s->m.l;
    zA2 = s->a.a; zF2 = s->a.f;
    CZ80.BC2.B.H = s->a.b; CZ80.BC2.B.L = s->a.c;
    CZ80.DE2.B.H = s->a.d; CZ80.DE2.B.L = s->a.e;
    CZ80.HL2.B.H = s->a.h; CZ80.HL2.B.L = s->a.l;
    zI  = s->i;   zR  = s->r;
    zIX = s->ix;  zIY = s->iy;
    Cz80_Set_Reg(&CZ80, CZ80_SP, s->sp);
    Cz80_Set_Reg(&CZ80, CZ80_PC, s->pc);
    Cz80_Set_Reg(&CZ80, CZ80_HALT, s->halted);
    Cz80_Set_Reg(&CZ80, CZ80_IFF1, s->iff1);
    Cz80_Set_Reg(&CZ80, CZ80_IFF2, s->iff2);
    zIM = s->im;
    Cz80_Set_Reg(&CZ80, CZ80_IRQ, s->irq_pending ? HOLD_LINE : CLEAR_LINE);
    return 0;
  }
#endif

fail:
  elprintf(EL_STATUS|EL_ANOMALY, "z80_unpack failed");
  z80_reset();
  z80_int();
  return -1;
}