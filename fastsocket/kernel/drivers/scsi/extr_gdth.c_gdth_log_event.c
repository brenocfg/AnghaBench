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
typedef  int /*<<< orphan*/  ushort ;
typedef  int /*<<< orphan*/  unchar ;
typedef  int /*<<< orphan*/  ulong32 ;
struct TYPE_8__ {int /*<<< orphan*/ * b; } ;
typedef  TYPE_3__ gdth_stackframe ;
struct TYPE_6__ {int ionode; scalar_t__ service; size_t status; } ;
struct TYPE_7__ {TYPE_1__ async; int /*<<< orphan*/ * stream; } ;
struct TYPE_9__ {scalar_t__ size; char* event_string; TYPE_2__ eu; } ;
typedef  TYPE_4__ gdth_evt_data ;

/* Variables and functions */
 scalar_t__ CACHESERVICE ; 
 scalar_t__ INDEX_OK (size_t,char**) ; 
 int /*<<< orphan*/  TRACE2 (char*) ; 
 char** async_cache_tab ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void gdth_log_event(gdth_evt_data *dvr, char *buffer)
{
    gdth_stackframe stack;
    char *f = NULL;
    int i,j;

    TRACE2(("gdth_log_event()\n"));
    if (dvr->size == 0) {
        if (buffer == NULL) {
            printk("Adapter %d: %s\n",dvr->eu.async.ionode,dvr->event_string); 
        } else {
            sprintf(buffer,"Adapter %d: %s\n",
                dvr->eu.async.ionode,dvr->event_string); 
        }
    } else if (dvr->eu.async.service == CACHESERVICE && 
        INDEX_OK(dvr->eu.async.status, async_cache_tab)) {
        TRACE2(("GDT: Async. event cache service, event no.: %d\n",
                dvr->eu.async.status));
        
        f = async_cache_tab[dvr->eu.async.status];
        
        /* i: parameter to push, j: stack element to fill */
        for (j=0,i=1; i < f[0]; i+=2) {
            switch (f[i+1]) {
              case 4:
                stack.b[j++] = *(ulong32*)&dvr->eu.stream[(int)f[i]];
                break;
              case 2:
                stack.b[j++] = *(ushort*)&dvr->eu.stream[(int)f[i]];
                break;
              case 1:
                stack.b[j++] = *(unchar*)&dvr->eu.stream[(int)f[i]];
                break;
              default:
                break;
            }
        }
        
        if (buffer == NULL) {
            printk(&f[(int)f[0]],stack); 
            printk("\n");
        } else {
            sprintf(buffer,&f[(int)f[0]],stack); 
        }

    } else {
        if (buffer == NULL) {
            printk("GDT HA %u, Unknown async. event service %d event no. %d\n",
                   dvr->eu.async.ionode,dvr->eu.async.service,dvr->eu.async.status);
        } else {
            sprintf(buffer,"GDT HA %u, Unknown async. event service %d event no. %d",
                    dvr->eu.async.ionode,dvr->eu.async.service,dvr->eu.async.status);
        }
    }
}