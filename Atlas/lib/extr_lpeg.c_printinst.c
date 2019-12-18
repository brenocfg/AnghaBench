#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t code; int aux; int offset; } ;
struct TYPE_10__ {TYPE_1__ i; int /*<<< orphan*/  buff; } ;
typedef  int /*<<< orphan*/  Opcode ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
#define  IAny 150 
#define  IBackCommit 149 
#define  ICall 148 
#define  IChar 147 
#define  IChoice 146 
#define  ICloseCapture 145 
#define  ICloseRunTime 144 
#define  ICommit 143 
#define  IEmptyCapture 142 
#define  IEmptyCaptureIdx 141 
#define  IFullCapture 140 
#define  IJmp 139 
#define  IOpenCall 138 
#define  IOpenCapture 137 
#define  IPartialCommit 136 
#define  ISet 135 
#define  ISpan 134 
#define  ISpanZ 133 
#define  ITestAny 132 
#define  ITestChar 131 
#define  ITestSet 130 
#define  ITestZSet 129 
#define  IZSet 128 
 int /*<<< orphan*/  getkind (TYPE_2__ const*) ; 
 int getoff (TYPE_2__ const*) ; 
 int /*<<< orphan*/  printcapkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printcharset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printjmp (TYPE_2__ const*,TYPE_2__ const*) ; 

__attribute__((used)) static void printinst (const Instruction *op, const Instruction *p) {
  const char *const names[] = {
    "any", "char", "set", "zset",
    "testany", "testchar", "testset", "testzset",
    "span", "spanz",
    "ret", "end",
    "choice", "jmp", "call", "open_call",
    "commit", "partial_commit", "back_commit", "failtwice", "fail", "giveup",
     "func",
     "fullcapture", "emptycapture", "emptycaptureidx", "opencapture",
     "closecapture", "closeruntime"
  };
  printf("%02ld: %s ", (long)(p - op), names[p->i.code]);
  switch ((Opcode)p->i.code) {
    case IChar: {
      printf("'%c'", p->i.aux);
      break;
    }
    case ITestChar: {
      printf("'%c'", p->i.aux);
      printjmp(op, p);
      break;
    }
    case IAny: {
      printf("* %d", p->i.aux);
      break;
    }
    case ITestAny: {
      printf("* %d", p->i.aux);
      printjmp(op, p);
      break;
    }
    case IFullCapture: case IOpenCapture:
    case IEmptyCapture: case IEmptyCaptureIdx:
    case ICloseCapture: case ICloseRunTime: {
      printcapkind(getkind(p));
      printf("(n = %d)  (off = %d)", getoff(p), p->i.offset);
      break;
    }
    case ISet: case IZSet: case ISpan: case ISpanZ: {
      printcharset((p+1)->buff);
      break;
    }
    case ITestSet: case ITestZSet: {
      printcharset((p+1)->buff);
      printjmp(op, p);
      break;
    }
    case IOpenCall: {
      printf("-> %d", p->i.offset);
      break;
    }
    case IChoice: {
      printjmp(op, p);
      printf(" (%d)", p->i.aux);
      break;
    }
    case IJmp: case ICall: case ICommit:
    case IPartialCommit: case IBackCommit: {
      printjmp(op, p);
      break;
    }
    default: break;
  }
  printf("\n");
}