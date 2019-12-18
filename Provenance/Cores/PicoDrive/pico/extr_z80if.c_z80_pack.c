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
struct TYPE_19__ {void* l; void* h; void* e; void* d; void* c; void* b; int /*<<< orphan*/  f; void* a; } ;
struct TYPE_18__ {void* l; void* h; void* e; void* d; void* c; void* b; int /*<<< orphan*/  f; void* a; } ;
struct z80_state {int halted; int iff1; int iff2; int irq_pending; int* irq_vector; int /*<<< orphan*/  im; scalar_t__ pc; scalar_t__ sp; void* iy; void* ix; int /*<<< orphan*/  r; void* i; TYPE_6__ a; TYPE_5__ m; int /*<<< orphan*/  magic; } ;
struct TYPE_16__ {void* L; void* H; } ;
struct TYPE_17__ {TYPE_3__ B; } ;
struct TYPE_14__ {void* L; void* H; } ;
struct TYPE_15__ {TYPE_1__ B; } ;
struct TYPE_21__ {void* L; void* H; } ;
struct TYPE_20__ {TYPE_8__ B; } ;
struct TYPE_22__ {TYPE_4__ HL2; TYPE_2__ DE2; TYPE_7__ BC2; } ;
typedef  TYPE_9__ cz80_struc ;
struct TYPE_13__ {int Z80IF; int z80irqvector; int /*<<< orphan*/  Z80_IRQ; int /*<<< orphan*/  Z80IM; scalar_t__ Z80PC_BASE; scalar_t__ Z80PC; scalar_t__ Z80SP_BASE; scalar_t__ Z80SP; int /*<<< orphan*/  spare; int /*<<< orphan*/  Z80F2; int /*<<< orphan*/  Z80F; } ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  A2 ; 
 int /*<<< orphan*/  BC ; 
 int /*<<< orphan*/  BC2 ; 
 TYPE_9__ CZ80 ; 
 int /*<<< orphan*/  CZ80_HALT ; 
 int /*<<< orphan*/  CZ80_IRQ ; 
 int /*<<< orphan*/  CZ80_PC ; 
 int /*<<< orphan*/  CZ80_SP ; 
 scalar_t__ Cz80_Get_Reg (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DE ; 
 int /*<<< orphan*/  DE2 ; 
 void* DRR16 (int /*<<< orphan*/ ) ; 
 void* DRR16H (int /*<<< orphan*/ ) ; 
 void* DRR16L (int /*<<< orphan*/ ) ; 
 void* DRR8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HL ; 
 int /*<<< orphan*/  HL2 ; 
 scalar_t__ HOLD_LINE ; 
 int /*<<< orphan*/  I ; 
 int /*<<< orphan*/  IX ; 
 int /*<<< orphan*/  IY ; 
 int /*<<< orphan*/  Z80_STATE_SIZE ; 
 TYPE_10__ drZ80 ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 void* zA ; 
 void* zA2 ; 
 void* zB ; 
 void* zC ; 
 void* zD ; 
 void* zE ; 
 int /*<<< orphan*/  zF ; 
 int /*<<< orphan*/  zF2 ; 
 void* zH ; 
 void* zI ; 
 int /*<<< orphan*/  zIFF1 ; 
 int /*<<< orphan*/  zIFF2 ; 
 int /*<<< orphan*/  zIM ; 
 void* zIX ; 
 void* zIY ; 
 void* zL ; 
 int /*<<< orphan*/  zR ; 

void z80_pack(void *data)
{
  struct z80_state *s = data;
  memset(data, 0, Z80_STATE_SIZE);
  strcpy(s->magic, "Z80");
#if defined(_USE_DRZ80)
  #define DRR8(n)   (drZ80.Z80##n >> 24)
  #define DRR16(n)  (drZ80.Z80##n >> 16)
  #define DRR16H(n) (drZ80.Z80##n >> 24)
  #define DRR16L(n) ((drZ80.Z80##n >> 16) & 0xff)
  s->m.a = DRR8(A);     s->m.f = drZ80.Z80F;
  s->m.b = DRR16H(BC);  s->m.c = DRR16L(BC);
  s->m.d = DRR16H(DE);  s->m.e = DRR16L(DE);
  s->m.h = DRR16H(HL);  s->m.l = DRR16L(HL);
  s->a.a = DRR8(A2);    s->a.f = drZ80.Z80F2;
  s->a.b = DRR16H(BC2); s->a.c = DRR16L(BC2);
  s->a.d = DRR16H(DE2); s->a.e = DRR16L(DE2);
  s->a.h = DRR16H(HL2); s->a.l = DRR16L(HL2);
  s->i = DRR8(I);       s->r = drZ80.spare;
  s->ix = DRR16(IX);    s->iy = DRR16(IY);
  s->sp = drZ80.Z80SP - drZ80.Z80SP_BASE;
  s->pc = drZ80.Z80PC - drZ80.Z80PC_BASE;
  s->halted = !!(drZ80.Z80IF & 4);
  s->iff1 = !!(drZ80.Z80IF & 1);
  s->iff2 = !!(drZ80.Z80IF & 2);
  s->im = drZ80.Z80IM;
  s->irq_pending = !!drZ80.Z80_IRQ;
  s->irq_vector[0] = drZ80.z80irqvector >> 16;
  s->irq_vector[1] = drZ80.z80irqvector >> 8;
  s->irq_vector[2] = drZ80.z80irqvector;
#elif defined(_USE_CZ80)
  {
    const cz80_struc *CPU = &CZ80;
    s->m.a = zA;  s->m.f = zF;
    s->m.b = zB;  s->m.c = zC;
    s->m.d = zD;  s->m.e = zE;
    s->m.h = zH;  s->m.l = zL;
    s->a.a = zA2; s->a.f = zF2;
    s->a.b = CZ80.BC2.B.H; s->a.c = CZ80.BC2.B.L;
    s->a.d = CZ80.DE2.B.H; s->a.e = CZ80.DE2.B.L;
    s->a.h = CZ80.HL2.B.H; s->a.l = CZ80.HL2.B.L;
    s->i  = zI;   s->r  = zR;
    s->ix = zIX;  s->iy = zIY;
    s->sp = Cz80_Get_Reg(&CZ80, CZ80_SP);
    s->pc = Cz80_Get_Reg(&CZ80, CZ80_PC);
    s->halted = !!Cz80_Get_Reg(&CZ80, CZ80_HALT);
    s->iff1 = !!zIFF1;
    s->iff2 = !!zIFF2;
    s->im = zIM;
    s->irq_pending = (Cz80_Get_Reg(&CZ80, CZ80_IRQ) == HOLD_LINE);
    s->irq_vector[0] = 0xff;
  }
#endif
}