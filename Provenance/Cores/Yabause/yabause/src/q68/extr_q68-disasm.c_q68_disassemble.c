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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  tagbuf ;
typedef  int int8_t ;
typedef  int const int16_t ;
struct TYPE_3__ {int mask; int test; char* format; } ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND (char*,...) ; 
 int /*<<< orphan*/  APPEND_CHAR (char const) ; 
 int READS16 (int /*<<< orphan*/ *,int) ; 
 void* READU16 (int /*<<< orphan*/ *,int) ; 
 void* READU32 (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* instructions ; 
 int lenof (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

const char *q68_disassemble(Q68State *state, uint32_t address,
                            int *nwords_ret)
{
    const uint32_t base_address = address;
    static char outbuf[1000];

    if (address % 2 != 0) {  // Odd addresses are invalid
        if (nwords_ret) {
            *nwords_ret = 1;
        }
        return "???";
    }

    uint16_t opcode = READU16(state, address);
    address += 2;
    const char *format = NULL;
    int i;
    for (i = 0; i < lenof(instructions); i++) {
        if ((opcode & instructions[i].mask) == instructions[i].test) {
            format = instructions[i].format;
            break;
        }
    }
    if (!format) {
        if (nwords_ret) {
            *nwords_ret = 1;
        }
        return "???";
    }

    int outlen = 0;
#define APPEND_CHAR(ch)  do { \
    if (outlen < sizeof(outbuf)-1) { \
        outbuf[outlen++] = (ch); \
        outbuf[outlen] = 0; \
    } \
} while (0)
#define APPEND(fmt,...)  do { \
    outlen += snprintf(&outbuf[outlen], sizeof(outbuf)-outlen, \
                       fmt , ## __VA_ARGS__); \
    if (outlen > sizeof(outbuf)-1) { \
        outlen = sizeof(outbuf)-1; \
    } \
} while (0)

    int inpos = 0;
    while (format[inpos] != 0) {
        if (format[inpos] == '<') {
            char tagbuf[100];
            int end = inpos+1;
            for (; format[end] != 0 && format[end] != '>'; end++) {
                if (end - (inpos+1) >= sizeof(tagbuf)) {
                    break;
                }
            }
            memcpy(tagbuf, &format[inpos+1], end - (inpos+1));
            tagbuf[end - (inpos+1)] = 0;
            if (format[end] != 0) {
                end++;
            }
            inpos = end;
            if (strncmp(tagbuf,"ea",2) == 0) {
                int mode, reg;
                char size;  // 'b', 'w', or 'l'
                if (strncmp(tagbuf,"ea2",3) == 0) {  // 2nd EA of MOVE insns
                    mode = opcode>>6 & 7;
                    reg  = opcode>>9 & 7;
                    size = tagbuf[4];
                } else {
                    mode = opcode>>3 & 7;
                    reg  = opcode>>0 & 7;
                    size = tagbuf[3];
                }
                switch (mode) {
                  case 0:
                    APPEND("D%d", reg);
                    break;
                  case 1:
                    APPEND("A%d", reg);
                    break;
                  case 2:
                    APPEND("(A%d)", reg);
                    break;
                  case 3:
                    APPEND("(A%d)+", reg);
                    break;
                  case 4:
                    APPEND("-(A%d)", reg);
                    break;
                  case 5: {
                    int16_t disp = READS16(state, address);
                    address += 2;
                    APPEND("%d(A%d)", disp, reg);
                    break;
                  }
                  case 6: {
                    uint16_t ext = READU16(state, address);
                    address += 2;
                    const int iregtype = ext>>15;
                    const int ireg     = ext>>12 & 7;
                    const int iregsize = ext>>11;
                    const int8_t disp  = ext & 0xFF;
                    APPEND("%d(A%d,%c%d.%c)", disp, reg,
                           iregtype ? 'A' : 'D', ireg, iregsize ? 'l' : 'w');
                    break;
                  }
                  case 7:
                    switch (reg) {
                      case 0: {
                        const uint16_t abs = READU16(state, address);
                        address += 2;
                        APPEND("($%X).w", abs);
                        break;
                      }
                      case 1: {
                        const uint32_t abs = READU32(state, address);
                        address += 4;
                        APPEND("($%X).l", abs);
                        break;
                      }
                      case 2: {
                        int16_t disp = READS16(state, address);
                        address += 2;
                        APPEND("$%X(PC)", (base_address+2) + disp);
                        break;
                      }
                      case 3: {
                        uint16_t ext = READU16(state, address);
                        address += 2;
                        const int iregtype = ext>>15;
                        const int ireg     = ext>>12 & 7;
                        const int iregsize = ext>>11;
                        const int8_t disp  = ext & 0xFF;
                        APPEND("$%X(PC,%c%d.%c)", (base_address+2) + disp,
                               iregtype ? 'A' : 'D', ireg, iregsize ? 'l' : 'w');
                        break;
                      }
                      case 4: {
                        uint32_t imm;
                        if (size == 'l') {
                            imm = READU32(state, address);
                            address += 4;
                        } else {
                            imm = READU16(state, address);
                            address += 2;
                        }
                        APPEND("#%s%X", imm<10 ? "" : "$", imm);
                        break;
                      }
                      default:
                        APPEND("???");
                        break;
                    }
                }
            } else if (strcmp(tagbuf,"reg") == 0) {
                APPEND("%d", opcode>>9 & 7);
            } else if (strcmp(tagbuf,"reg0") == 0) {
                APPEND("%d", opcode>>0 & 7);
            } else if (strcmp(tagbuf,"count") == 0) {
                APPEND("%d", opcode>>9 & 7 ?: 8);
            } else if (strcmp(tagbuf,"trap") == 0) {
                APPEND("%d", opcode>>0 & 15);
            } else if (strcmp(tagbuf,"quick8") == 0) {
                APPEND("%d", (int8_t)(opcode & 0xFF));
            } else if (strncmp(tagbuf,"imm8",4) == 0) {
                uint8_t imm8 = READU16(state, address); // Upper 8 bits ignored
                imm8 &= 0xFF;
                address += 2;
                if (tagbuf[4] == 'd') {
                    APPEND("%d", imm8);
                } else if (tagbuf[4] == 'x') {
                    APPEND("$%02X", imm8);
                } else {
                    APPEND("%s%X", imm8<10 ? "" : "$", imm8);
                }
            } else if (strncmp(tagbuf,"imm16",5) == 0) {
                uint16_t imm16 = READU16(state, address);
                address += 2;
                if (tagbuf[5] == 'd') {
                    APPEND("%d", imm16);
                } else if (tagbuf[5] == 'x') {
                    APPEND("$%04X", imm16);
                } else {
                    APPEND("%s%X", imm16<10 ? "" : "$", imm16);
                }
            } else if (strcmp(tagbuf,"pcrel8") == 0) {
                int8_t disp8 = opcode & 0xFF;
                APPEND("$%X", (base_address+2) + disp8);
            } else if (strcmp(tagbuf,"pcrel16") == 0) {
                int16_t disp16 = READS16(state, address);
                address += 2;
                APPEND("$%X", (base_address+2) + disp16);
            } else if (strcmp(tagbuf,"reglist") == 0
                       || strcmp(tagbuf,"tsilger") == 0) {
                uint16_t reglist = READU16(state, address);
                address += 2;
                if (strcmp(tagbuf,"tsilger") == 0) {  // "reglist" backwards
                    /* Predecrement-mode register list, so flip it around */
                    uint16_t temp = reglist;
                    reglist = 0;
                    while (temp) {
                        reglist <<= 1;
                        if (temp & 1) {
                            reglist |= 1;
                        }
                        temp >>= 1;
                    }
                }
                char listbuf[3*16];  // Buffer for generating register list
                unsigned int listlen = 0;  // strlen(listbuf)
                unsigned int last = 0;     // State of the previous bit
                unsigned int regnum = 0;   // Current register number (0-15)
                while (reglist) {
                    if (reglist & 1) {
                        if (last) {
                            if (listlen >= 3 && listbuf[listlen-3] == '-') {
                                listlen -= 2;
                            } else {
                                listbuf[listlen++] = '-';
                            }
                        } else {
                            if (listlen > 0) {
                                listbuf[listlen++] = '/';
                            }
                        }
                        listbuf[listlen++] = regnum<8 ? 'D' : 'A';
                        listbuf[listlen++] = '0' + (regnum % 8);
                    }
                    last = reglist & 1;
                    regnum++;
                    reglist >>= 1;
                }
                listbuf[listlen] = 0;
                APPEND("%s", listbuf);
            } else {
                APPEND("<%s>", tagbuf);
            }
        } else {
            APPEND_CHAR(format[inpos]);
            inpos++;
        }
    }

    if (nwords_ret) {
        *nwords_ret = (address - base_address) / 2;
    }
    return outbuf;
}