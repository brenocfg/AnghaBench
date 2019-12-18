#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int code; int /*<<< orphan*/  aux; } ;
struct TYPE_5__ {int* buff; TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;
typedef  int* Charset ;

/* Variables and functions */
#define  IChar 133 
#define  ISet 132 
#define  ITestChar 131 
#define  ITestSet 130 
#define  ITestZSet 129 
#define  IZSet 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t i ; 
 int /*<<< orphan*/  loopset (size_t,int) ; 
 int /*<<< orphan*/  setchar (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testchar (int*,char) ; 

__attribute__((used)) static void fillcharset (Instruction *p, Charset cs) {
  switch (p[0].i.code) {
    case IZSet: case ITestZSet:
      assert(testchar(p[1].buff, '\0'));
      /* go through */
    case ISet: case ITestSet: {
      loopset(i, cs[i] = p[1].buff[i]);
      break;
    }
    case IChar: case ITestChar: {
      loopset(i, cs[i] = 0);
      setchar(cs, p[0].i.aux);
      break;
    }
    default: {  /* any char may start unhandled instructions */
      loopset(i, cs[i] = 0xff);
      break;
    }
  }
}