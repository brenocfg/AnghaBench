#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_4__ {int current_PC; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int ACCESS_READ ; 
 int ACCESS_WRITE ; 
#define  EA_DISPLACEMENT 136 
#define  EA_INDEX 135 
#define  EA_INDIRECT 134 
#define  EA_MISC_ABSOLUTE_L 133 
#define  EA_MISC_ABSOLUTE_W 132 
#define  EA_MISC_PCREL 131 
#define  EA_MISC_PCREL_INDEX 130 
 unsigned int EA_MODE (int) ; 
#define  EA_POSTINCREMENT 129 
#define  EA_PREDECREMENT 128 
 unsigned int EA_REG (int) ; 
 int IFETCH (TYPE_1__*) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_ABSOLUTE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_ABS_INDEX_L (int /*<<< orphan*/ ,int const,unsigned int const) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_ABS_INDEX_W (int /*<<< orphan*/ ,int const,unsigned int const) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_DISP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_INDEX_L (int /*<<< orphan*/ ,int,unsigned int const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_INDEX_W (int /*<<< orphan*/ ,int,unsigned int const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_INDIRECT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_POSTINC (int /*<<< orphan*/ ,int,unsigned int const) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_POSTINC_A7_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_PREDEC (int /*<<< orphan*/ ,int,unsigned int const) ; 
 int /*<<< orphan*/  JIT_EMIT_RESOLVE_PREDEC_A7_B (int /*<<< orphan*/ ) ; 
 int SIZE_L ; 
 unsigned int SIZE_TO_BYTES (int) ; 
 int /*<<< orphan*/  current_entry ; 

__attribute__((used)) static int ea_resolve(Q68State *state, uint32_t opcode, int size,
                      int access_type)
{
    const unsigned int mode  = EA_MODE(opcode);
    const unsigned int reg   = EA_REG(opcode);
    const unsigned int bytes = SIZE_TO_BYTES(size);

    static const int base_cycles[8] = {0, 0, 4, 4, 6, 8, 10, 0};
    int cycles = base_cycles[mode] + (size==SIZE_L ? 4 : 0);

    switch (mode) {
      case EA_INDIRECT:
        JIT_EMIT_RESOLVE_INDIRECT(current_entry, (8+reg)*4);
        break;
      case EA_POSTINCREMENT:
        if (bytes == 1 && reg == 7) {  // A7 must stay even
            JIT_EMIT_RESOLVE_POSTINC_A7_B(current_entry);
        } else {
            JIT_EMIT_RESOLVE_POSTINC(current_entry, (8+reg)*4, bytes);
        }
        break;
      case EA_PREDECREMENT:
        if (access_type == ACCESS_WRITE) {
            /* 2-cycle penalty not applied to write-only accesses
             * (MOVE and MOVEM) */
            cycles -= 2;
        }
        if (bytes == 1 && reg == 7) {  // A7 must stay even
            JIT_EMIT_RESOLVE_PREDEC_A7_B(current_entry);
        } else {
            JIT_EMIT_RESOLVE_PREDEC(current_entry, (8+reg)*4, bytes);
        }
        break;
      case EA_DISPLACEMENT:
        JIT_EMIT_RESOLVE_DISP(current_entry, (8+reg)*4, (int16_t)IFETCH(state));
        break;
      case EA_INDEX: {
        const uint16_t ext = IFETCH(state);
        const unsigned int ireg = ext >> 12;  // 0..15
        const int8_t disp = (int8_t)ext;
        if (ext & 0x0800) {
            JIT_EMIT_RESOLVE_INDEX_L(current_entry, (8+reg)*4, ireg*4, disp);
        } else {
            JIT_EMIT_RESOLVE_INDEX_W(current_entry, (8+reg)*4, ireg*4, disp);
        }
        break;
      }
      default:  /* case EA_MISC */
        switch (reg) {
          case EA_MISC_ABSOLUTE_W:
            cycles += 8;
            JIT_EMIT_RESOLVE_ABSOLUTE(current_entry, (int16_t)IFETCH(state));
            break;
          case EA_MISC_ABSOLUTE_L: {
            cycles += 12;
            uint32_t addr = IFETCH(state) << 16;
            addr |= (uint16_t)IFETCH(state);
            JIT_EMIT_RESOLVE_ABSOLUTE(current_entry, addr);
            break;
          }
          case EA_MISC_PCREL:
            if (access_type != ACCESS_READ) {
                return -1;
            } else {
                cycles += 8;
                JIT_EMIT_RESOLVE_ABSOLUTE(
                    current_entry, state->current_PC + (int16_t)IFETCH(state)
                );
            }
            break;
          case EA_MISC_PCREL_INDEX:
            if (access_type != ACCESS_READ) {
                return -1;
            } else {
                cycles += 10;
                const uint16_t ext = IFETCH(state);
                const unsigned int ireg = ext >> 12;  // 0..15
                const int32_t disp = (int32_t)((int8_t)ext);
                if (ext & 0x0800) {
                    JIT_EMIT_RESOLVE_ABS_INDEX_L(
                        current_entry, state->current_PC + disp, ireg*4
                    );
                } else {
                    JIT_EMIT_RESOLVE_ABS_INDEX_W(
                        current_entry, state->current_PC + disp, ireg*4
                    );
                }
            }
            break;
          default:
            return -1;
        }
    }
    return cycles;
}