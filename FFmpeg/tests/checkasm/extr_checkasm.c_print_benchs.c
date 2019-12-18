#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nop_time; } ;
struct TYPE_6__ {int iterations; int cycles; } ;
struct TYPE_7__ {scalar_t__ cpu; TYPE_1__ perf; struct TYPE_7__* next; } ;
struct TYPE_8__ {char* name; struct TYPE_8__** child; TYPE_2__ versions; } ;
typedef  TYPE_1__ CheckasmPerf ;
typedef  TYPE_2__ CheckasmFuncVersion ;
typedef  TYPE_3__ CheckasmFunc ;

/* Variables and functions */
 char* cpu_suffix (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int,int) ; 
 TYPE_4__ state ; 

__attribute__((used)) static void print_benchs(CheckasmFunc *f)
{
    if (f) {
        print_benchs(f->child[0]);

        /* Only print functions with at least one assembly version */
        if (f->versions.cpu || f->versions.next) {
            CheckasmFuncVersion *v = &f->versions;
            do {
                CheckasmPerf *p = &v->perf;
                if (p->iterations) {
                    int decicycles = (10*p->cycles/p->iterations - state.nop_time) / 4;
                    printf("%s_%s: %d.%d\n", f->name, cpu_suffix(v->cpu), decicycles/10, decicycles%10);
                }
            } while ((v = v->next));
        }

        print_benchs(f->child[1]);
    }
}