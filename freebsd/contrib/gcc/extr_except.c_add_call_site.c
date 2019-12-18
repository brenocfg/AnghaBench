#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct call_site_record {int action; int /*<<< orphan*/  landing_pad; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int call_site_data_used; int call_site_data_size; struct call_site_record* call_site_data; } ;

/* Variables and functions */
 int call_site_base ; 
 TYPE_2__* cfun ; 
 struct call_site_record* ggc_realloc (struct call_site_record*,int) ; 

__attribute__((used)) static int
add_call_site (rtx landing_pad, int action)
{
  struct call_site_record *data = cfun->eh->call_site_data;
  int used = cfun->eh->call_site_data_used;
  int size = cfun->eh->call_site_data_size;

  if (used >= size)
    {
      size = (size ? size * 2 : 64);
      data = ggc_realloc (data, sizeof (*data) * size);
      cfun->eh->call_site_data = data;
      cfun->eh->call_site_data_size = size;
    }

  data[used].landing_pad = landing_pad;
  data[used].action = action;

  cfun->eh->call_site_data_used = used + 1;

  return used + call_site_base;
}