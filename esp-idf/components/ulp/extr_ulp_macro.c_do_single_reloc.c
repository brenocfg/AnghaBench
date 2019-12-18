#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int imm; int /*<<< orphan*/  sel; int /*<<< orphan*/  sub_opcode; int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {int addr; int /*<<< orphan*/  reg; } ;
struct TYPE_9__ {int offset; int sign; int /*<<< orphan*/  sub_opcode; int /*<<< orphan*/  opcode; } ;
struct TYPE_12__ {TYPE_3__ alu_imm; TYPE_2__ bx; TYPE_1__ b; } ;
typedef  TYPE_4__ ulp_insn_t ;
typedef  int uint32_t ;
struct TYPE_13__ {int addr; int type; } ;
typedef  TYPE_5__ reloc_info_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_SEL_MOV ; 
 int /*<<< orphan*/  ESP_ERR_ULP_BRANCH_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  OPCODE_ALU ; 
 int /*<<< orphan*/  OPCODE_BRANCH ; 
#define  RELOC_TYPE_BRANCH 132 
#define  RELOC_TYPE_LABELPC 131 
 int /*<<< orphan*/  SUB_OPCODE_ALU_IMM ; 
#define  SUB_OPCODE_B 130 
#define  SUB_OPCODE_BS 129 
#define  SUB_OPCODE_BX 128 
 int /*<<< orphan*/  TAG ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t do_single_reloc(ulp_insn_t* program, uint32_t load_addr,
        reloc_info_t label_info, reloc_info_t the_reloc)
{
    size_t insn_offset = the_reloc.addr - load_addr;
    ulp_insn_t* insn = &program[insn_offset];

    switch (the_reloc.type) {
        case RELOC_TYPE_BRANCH: {
            // B, BS and BX have the same layout of opcode/sub_opcode fields,
            // and share the same opcode. B and BS also have the same layout of
            // offset and sign fields.
            assert(insn->b.opcode == OPCODE_BRANCH
                    && "branch macro was applied to a non-branch instruction");
            switch (insn->b.sub_opcode) {
                case SUB_OPCODE_B:
                case SUB_OPCODE_BS:{
                    int32_t offset = ((int32_t) label_info.addr) - ((int32_t) the_reloc.addr);
                    uint32_t abs_offset = abs(offset);
                    uint32_t sign = (offset >= 0) ? 0 : 1;
                    if (abs_offset > 127) {
                        ESP_LOGW(TAG, "target out of range: branch from %x to %x",
                                the_reloc.addr, label_info.addr);
                        return ESP_ERR_ULP_BRANCH_OUT_OF_RANGE;
                    }
                    insn->b.offset = abs_offset; //== insn->bs.offset = abs_offset;
                    insn->b.sign = sign;         //== insn->bs.sign = sign;
                    break;
                }
                case SUB_OPCODE_BX:{
                    assert(insn->bx.reg == 0 &&
                            "relocation applied to a jump with offset in register");
                    insn->bx.addr = label_info.addr;
                    break;
                }
                default:
                    assert(false && "unexpected branch sub-opcode");
            }
            break;
        }
        case RELOC_TYPE_LABELPC: {
            assert((insn->alu_imm.opcode == OPCODE_ALU && insn->alu_imm.sub_opcode == SUB_OPCODE_ALU_IMM && insn->alu_imm.sel == ALU_SEL_MOV)
                        && "pc macro was applied to an incompatible instruction");
            insn->alu_imm.imm = label_info.addr;
            break;
        }
        default:
            assert(false && "unknown reloc type");
    }
    return ESP_OK;
}