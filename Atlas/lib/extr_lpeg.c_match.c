#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lua_Integer ;
typedef  int byte ;
struct TYPE_22__ {char const* s; int siz; int /*<<< orphan*/  kind; int /*<<< orphan*/  idx; } ;
struct TYPE_19__ {int aux; int /*<<< orphan*/  offset; int /*<<< orphan*/  code; } ;
struct TYPE_21__ {char* (* f ) (int /*<<< orphan*/ ,char const*,char const*,char const*) ;TYPE_1__ i; int /*<<< orphan*/  buff; } ;
struct TYPE_20__ {char const* s; int caplevel; TYPE_3__ const* p; } ;
typedef  TYPE_2__ Stack ;
typedef  int /*<<< orphan*/  Opcode ;
typedef  TYPE_3__ const Instruction ;
typedef  TYPE_4__ Capture ;

/* Variables and functions */
 int /*<<< orphan*/  CHARSETINSTSIZE ; 
 int /*<<< orphan*/  Cclose ; 
#define  IAny 156 
#define  IBackCommit 155 
#define  ICall 154 
#define  IChar 153 
#define  IChoice 152 
#define  ICloseCapture 151 
#define  ICloseRunTime 150 
#define  ICommit 149 
#define  IEmptyCapture 148 
#define  IEmptyCaptureIdx 147 
#define  IEnd 146 
#define  IFail 145 
#define  IFailTwice 144 
#define  IFullCapture 143 
#define  IFunc 142 
#define  IGiveup 141 
#define  IJmp 140 
 int IMAXCAPTURES ; 
#define  IOpenCall 139 
#define  IOpenCapture 138 
#define  IPartialCommit 137 
#define  IRet 136 
#define  ISet 135 
#define  ISpan 134 
#define  ISpanZ 133 
#define  ITestAny 132 
#define  ITestChar 131 
#define  ITestSet 130 
#define  ITestZSet 129 
#define  IZSet 128 
 int MAXBACK ; 
 char const* UCHAR_MAX ; 
 int /*<<< orphan*/  adddyncaptures (char const*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ const* dest (int /*<<< orphan*/ ,TYPE_3__ const*) ; 
 TYPE_4__* doublecap (int /*<<< orphan*/ *,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  getkind (TYPE_3__ const*) ; 
 int /*<<< orphan*/  getoff (TYPE_3__ const*) ; 
 TYPE_3__ const giveup ; 
 char const* luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  penvidx (int) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,int) ; 
 int /*<<< orphan*/  printinst (TYPE_3__ const*,TYPE_3__ const*) ; 
 int runtimecap (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,char const*,char const*,int) ; 
 char* stub1 (int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  testchar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  val2str (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char *match (lua_State *L,
                          const char *o, const char *s, const char *e,
                          Instruction *op, Capture *capture, int ptop) {
  Stack stackbase[MAXBACK];
  Stack *stacklimit = stackbase + MAXBACK;
  Stack *stack = stackbase;  /* point to first empty slot in stack */
  int capsize = IMAXCAPTURES;
  int captop = 0;  /* point to first empty slot in captures */
  const Instruction *p = op;
  stack->p = &giveup; stack->s = s; stack->caplevel = 0; stack++;
  for (;;) {
#if defined(DEBUG)
      printf("s: |%s| stck: %d c: %d  ", s, stack - stackbase, captop);
      printinst(op, p);
#endif
    switch ((Opcode)p->i.code) {
      case IEnd: {
        assert(stack == stackbase + 1);
        capture[captop].kind = Cclose;
        capture[captop].s = NULL;
        return s;
      }
      case IGiveup: {
        assert(stack == stackbase);
        return NULL;
      }
      case IRet: {
        assert(stack > stackbase && (stack - 1)->s == NULL);
        p = (--stack)->p;
        continue;
      }
      case IAny: {
        int n = p->i.aux;
        if (n > e - s) goto fail;
        else { p++; s += n; }
        continue;
      }
      case ITestAny: {
        int n = p->i.aux;
        if (n > e - s) p += p->i.offset;
        else { p++; s += n; }
        continue;
      }
      case IChar: {
        if ((byte)*s != p->i.aux || s >= e) goto fail;
        else { p++; s++; }
        continue;
      }
      case ITestChar: {
        if ((byte)*s != p->i.aux || s >= e) p += p->i.offset;
        else { p++; s++; }
        continue;
      }
      case ISet: {
        int c = (unsigned char)*s;
        if (!testchar((p+1)->buff, c)) goto fail;
        else { p += CHARSETINSTSIZE; s++; }
        continue;
      }
      case ITestSet: {
        int c = (unsigned char)*s;
        if (!testchar((p+1)->buff, c)) p += p->i.offset;
        else { p += CHARSETINSTSIZE; s++; }
        continue;
      }
      case IZSet: {
        int c = (unsigned char)*s;
        if (!testchar((p+1)->buff, c) || s >= e) goto fail;
        else { p += CHARSETINSTSIZE; s++; }
        continue;
      }
      case ITestZSet: {
        int c = (unsigned char)*s;
        if (!testchar((p+1)->buff, c) || s >= e) p += p->i.offset;
        else { p += CHARSETINSTSIZE; s++; }
        continue;
      }
      case ISpan: {
        for (;; s++) {
          int c = (unsigned char)*s;
          if (!testchar((p+1)->buff, c)) break;
        }
        p += CHARSETINSTSIZE;
        continue;
      }
      case ISpanZ: {
        for (; s < e; s++) {
          int c = (unsigned char)*s;
          if (!testchar((p+1)->buff, c)) break;
        }
        p += CHARSETINSTSIZE;
        continue;
      }
      case IFunc: {
        const char *r = (p+1)->f((p+2)->buff, o, s, e);
        if (r == NULL) goto fail;
        s = r;
        p += p->i.offset;
        continue;
      }
      case IJmp: {
        p += p->i.offset;
        continue;
      }
      case IChoice: {
        if (stack >= stacklimit)
          return (luaL_error(L, "too many pending calls/choices"), (char *)0);
        stack->p = dest(0, p);
        stack->s = s - p->i.aux;
        stack->caplevel = captop;
        stack++;
        p++;
        continue;
      }
      case ICall: {
        if (stack >= stacklimit)
          return (luaL_error(L, "too many pending calls/choices"), (char *)0);
        stack->s = NULL;
        stack->p = p + 1;  /* save return address */
        stack++;
        p += p->i.offset;
        continue;
      }
      case ICommit: {
        assert(stack > stackbase && (stack - 1)->s != NULL);
        stack--;
        p += p->i.offset;
        continue;
      }
      case IPartialCommit: {
        assert(stack > stackbase && (stack - 1)->s != NULL);
        (stack - 1)->s = s;
        (stack - 1)->caplevel = captop;
        p += p->i.offset;
        continue;
      }
      case IBackCommit: {
        assert(stack > stackbase && (stack - 1)->s != NULL);
        s = (--stack)->s;
        p += p->i.offset;
        continue;
      }
      case IFailTwice:
        assert(stack > stackbase);
        stack--;
        /* go through */
      case IFail:
      fail: { /* pattern failed: try to backtrack */
        do {  /* remove pending calls */
          assert(stack > stackbase);
          s = (--stack)->s;
        } while (s == NULL);
        captop = stack->caplevel;
        p = stack->p;
        continue;
      }
      case ICloseRunTime: {
        int fr = lua_gettop(L) + 1;  /* stack index of first result */
        int ncap = runtimecap(L, capture + captop, capture, o, s, ptop);
        lua_Integer res = lua_tointeger(L, fr) - 1;  /* offset */
        int n = lua_gettop(L) - fr;  /* number of new captures */
        if (res == -1) {  /* may not be a number */
          if (!lua_toboolean(L, fr)) {  /* false value? */
            lua_settop(L, fr - 1);  /* remove results */
            goto fail;  /* and fail */
          }
          else if (lua_isboolean(L, fr))  /* true? */
            res = s - o;  /* keep current position */
        }
        if (res < s - o || res > e - o)
          luaL_error(L, "invalid position returned by match-time capture");
        s = o + res;  /* update current position */
        captop -= ncap;  /* remove nested captures */
        lua_remove(L, fr);  /* remove first result (offset) */
        if (n > 0) {  /* captures? */
          if ((captop += n + 1) >= capsize) {
            capture = doublecap(L, capture, captop, ptop);
            capsize = 2 * captop;
          }
          adddyncaptures(s, capture + captop - n - 1, n, fr);
        }
        p++;
        continue;
      }
      case ICloseCapture: {
        const char *s1 = s - getoff(p);
        assert(captop > 0);
        if (capture[captop - 1].siz == 0 &&
            s1 - capture[captop - 1].s < UCHAR_MAX) {
          capture[captop - 1].siz = s1 - capture[captop - 1].s + 1;
          p++;
          continue;
        }
        else {
          capture[captop].siz = 1;  /* mark entry as closed */
          goto capture;
        }
      }
      case IEmptyCapture: case IEmptyCaptureIdx:
        capture[captop].siz = 1;  /* mark entry as closed */
        goto capture;
      case IOpenCapture:
        capture[captop].siz = 0;  /* mark entry as open */
        goto capture;
      case IFullCapture:
        capture[captop].siz = getoff(p) + 1;  /* save capture size */
      capture: {
        capture[captop].s = s - getoff(p);
        capture[captop].idx = p->i.offset;
        capture[captop].kind = getkind(p);
        if (++captop >= capsize) {
          capture = doublecap(L, capture, captop, ptop);
          capsize = 2 * captop;
        }
        p++;
        continue;
      }
      case IOpenCall: {
        lua_rawgeti(L, penvidx(ptop), p->i.offset);
        luaL_error(L, "reference to %s outside a grammar", val2str(L, -1));
      }
      default: assert(0); return NULL;
    }
  }
}