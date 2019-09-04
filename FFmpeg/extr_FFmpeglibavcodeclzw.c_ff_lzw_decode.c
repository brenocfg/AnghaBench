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
typedef  int /*<<< orphan*/  uint8_t ;
struct LZWState {int end_code; int oc; int fc; int clear_code; size_t cursize; size_t codesize; int slot; int newcodes; int top_slot; int* suffix; int* prefix; size_t extra_slot; int /*<<< orphan*/ * sp; void* curmask; int /*<<< orphan*/ * stack; } ;
typedef  int /*<<< orphan*/  LZWState ;

/* Variables and functions */
 int LZW_MAXBITS ; 
 int lzw_get_code (struct LZWState*) ; 
 void** mask ; 

int ff_lzw_decode(LZWState *p, uint8_t *buf, int len){
    int l, c, code, oc, fc;
    uint8_t *sp;
    struct LZWState *s = (struct LZWState *)p;

    if (s->end_code < 0)
        return 0;

    l = len;
    sp = s->sp;
    oc = s->oc;
    fc = s->fc;

    for (;;) {
        while (sp > s->stack) {
            *buf++ = *(--sp);
            if ((--l) == 0)
                goto the_end;
        }
        c = lzw_get_code(s);
        if (c == s->end_code) {
            break;
        } else if (c == s->clear_code) {
            s->cursize = s->codesize + 1;
            s->curmask = mask[s->cursize];
            s->slot = s->newcodes;
            s->top_slot = 1 << s->cursize;
            fc= oc= -1;
        } else {
            code = c;
            if (code == s->slot && fc>=0) {
                *sp++ = fc;
                code = oc;
            }else if(code >= s->slot)
                break;
            while (code >= s->newcodes) {
                *sp++ = s->suffix[code];
                code = s->prefix[code];
            }
            *sp++ = code;
            if (s->slot < s->top_slot && oc>=0) {
                s->suffix[s->slot] = code;
                s->prefix[s->slot++] = oc;
            }
            fc = code;
            oc = c;
            if (s->slot >= s->top_slot - s->extra_slot) {
                if (s->cursize < LZW_MAXBITS) {
                    s->top_slot <<= 1;
                    s->curmask = mask[++s->cursize];
                }
            }
        }
    }
    s->end_code = -1;
  the_end:
    s->sp = sp;
    s->oc = oc;
    s->fc = fc;
    return len - l;
}