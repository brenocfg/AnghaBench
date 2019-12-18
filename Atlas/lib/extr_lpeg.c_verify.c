#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {int const code; int offset; int /*<<< orphan*/  aux; } ;
struct TYPE_12__ {char* (* f ) (int /*<<< orphan*/ ,char const*,char const*,char const*) ;TYPE_1__ i; int /*<<< orphan*/  buff; } ;
struct TYPE_11__ {char const* s; TYPE_3__ const* p; } ;
typedef  TYPE_2__ Stack ;
typedef  int /*<<< orphan*/  Opcode ;
typedef  TYPE_3__ const Instruction ;

/* Variables and functions */
#define  IAny 155 
#define  IBackCommit 154 
#define  ICall 153 
#define  IChar 152 
#define  IChoice 151 
#define  ICloseCapture 150 
#define  ICloseRunTime 149 
#define  ICommit 148 
#define  IEmptyCapture 147 
#define  IEmptyCaptureIdx 146 
#define  IEnd 145 
#define  IFail 144 
#define  IFailTwice 143 
#define  IFullCapture 142 
#define  IFunc 141 
#define  IJmp 140 
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
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ const* dest (int /*<<< orphan*/ ,TYPE_3__ const*) ; 
 int /*<<< orphan*/  getposition (int /*<<< orphan*/ *,int,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  sizei (TYPE_3__ const*) ; 
 char* stub1 (int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  val2str (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int verify (lua_State *L, Instruction *op, const Instruction *p,
                   Instruction *e, int postable, int rule) {
  static const char dummy[] = "";
  Stack back[MAXBACK];
  int backtop = 0;  /* point to first empty slot in back */
  while (p != e) {
    switch ((Opcode)p->i.code) {
      case IRet: {
        p = back[--backtop].p;
        continue;
      }
      case IChoice: {
        if (backtop >= MAXBACK)
          return luaL_error(L, "too many pending calls/choices");
        back[backtop].p = dest(0, p);
        back[backtop++].s = dummy;
        p++;
        continue;
      }
      case ICall: {
        assert((p + 1)->i.code != IRet);  /* no tail call */
        if (backtop >= MAXBACK)
          return luaL_error(L, "too many pending calls/choices");
        back[backtop].s = NULL;
        back[backtop++].p = p + 1;
        goto dojmp;
      }
      case IOpenCall: {
        int i;
        if (postable == 0)  /* grammar still not fixed? */
          goto fail;  /* to be verified later */
        for (i = 0; i < backtop; i++) {
          if (back[i].s == NULL && back[i].p == p + 1)
            return luaL_error(L, "%s is left recursive", val2str(L, rule));
        }
        if (backtop >= MAXBACK)
          return luaL_error(L, "too many pending calls/choices");
        back[backtop].s = NULL;
        back[backtop++].p = p + 1;
        p = op + getposition(L, postable, p->i.offset);
        continue;
      }
      case IBackCommit:
      case ICommit: {
        assert(backtop > 0 && p->i.offset > 0);
        backtop--;
        goto dojmp;
      }
      case IPartialCommit: {
        assert(backtop > 0);
        if (p->i.offset > 0) goto dojmp;  /* forward jump */
        else {  /* loop will be detected when checking corresponding rule */
          assert(postable != 0);
          backtop--;
          p++;  /* just go on now */
          continue;
        }
      }
      case ITestAny:
      case ITestChar:  /* all these cases jump for empty subject */
      case ITestSet:
      case ITestZSet:
      case IJmp: 
      dojmp: {
        p += p->i.offset;
        continue;
      }
      case IAny:
      case IChar:
      case ISet:
      case IZSet:
      case IFailTwice:  /* assume that first level failed; try to backtrack */
        goto fail;
      case IFail: {
        if (p->i.aux) {  /* is an 'and' predicate? */
          assert((p - 1)->i.code == IBackCommit && (p - 1)->i.offset == 2);
          p++;  /* pretend it succeeded and go ahead */
          continue;
        }
        /* else go through */
      }
      fail: { /* pattern failed: try to backtrack */
        do {
          if (backtop-- == 0)
            return 1;  /* no more backtracking */
        } while (back[backtop].s == NULL);
        p = back[backtop].p;
        continue;
      }
      case ISpan: case ISpanZ:
      case IOpenCapture: case ICloseCapture:
      case IEmptyCapture: case IEmptyCaptureIdx:
      case IFullCapture: {
        p += sizei(p);
        continue;
      }
      case ICloseRunTime: {
        goto fail;  /* be liberal in this case */
      }
      case IFunc: {
        const char *r = (p+1)->f((p+2)->buff, dummy, dummy, dummy);
        if (r == NULL) goto fail;
        p += p->i.offset;
        continue;
      }
      case IEnd:  /* cannot happen (should stop before it) */
      default: assert(0); return 0;
    }
  }
  assert(backtop == 0);
  return 0;
}