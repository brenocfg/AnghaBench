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
typedef  size_t dword ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;
typedef  void* byte ;
struct TYPE_5__ {int sec; int usec; TYPE_1__* hDbg; scalar_t__* drvName; } ;
struct TYPE_4__ {scalar_t__* drvTag; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 TYPE_2__* clients ; 
 int /*<<< orphan*/  dbg_q_lock ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (void**,scalar_t__*,int) ; 
 int min (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 

int diva_get_driver_info (dword id, byte* data, int data_length) {
  diva_os_spin_lock_magic_t old_irql;
  byte* p = data;
  int to_copy;

  if (!data || !id || (data_length < 17) ||
      (id >= ARRAY_SIZE(clients))) {
    return (-1);
  }

  diva_os_enter_spin_lock (&dbg_q_lock, &old_irql, "driver info");

  if (clients[id].hDbg) {
    *p++ = 1;
    *p++ = (byte)clients[id].sec; /* save seconds */
    *p++ = (byte)(clients[id].sec >>  8);
    *p++ = (byte)(clients[id].sec >> 16);
    *p++ = (byte)(clients[id].sec >> 24);

    *p++ = (byte)(clients[id].usec/1000); /* save mseconds */
    *p++ = (byte)((clients[id].usec/1000) >>  8);
    *p++ = (byte)((clients[id].usec/1000) >> 16);
    *p++ = (byte)((clients[id].usec/1000) >> 24);

    data_length -= 9;

    if ((to_copy = min(strlen(clients[id].drvName), (size_t)(data_length-1)))) {
      memcpy (p, clients[id].drvName, to_copy);
      p += to_copy;
      data_length -= to_copy;
      if ((data_length >= 4) && clients[id].hDbg->drvTag[0]) {
        *p++ = '(';
        data_length -= 1;
        if ((to_copy = min(strlen(clients[id].hDbg->drvTag), (size_t)(data_length-2)))) {
          memcpy (p, clients[id].hDbg->drvTag, to_copy);
          p += to_copy;
          data_length -= to_copy;
          if (data_length >= 2) {
            *p++ = ')';
            data_length--;
          }
        }
      }
    }
  }
  *p++ = 0;

  diva_os_leave_spin_lock (&dbg_q_lock, &old_irql, "driver info");

  return (p - data);
}