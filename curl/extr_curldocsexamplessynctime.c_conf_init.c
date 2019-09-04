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
struct TYPE_3__ {scalar_t__* timeserver; scalar_t__* proxy_user; scalar_t__* http_proxy; } ;
typedef  TYPE_1__ conf_t ;

/* Variables and functions */
 int MAX_STRING1 ; 

int conf_init(conf_t *conf)
{
  int i;

  *conf->http_proxy       = 0;
  for(i = 0; i<MAX_STRING1; i++)
    conf->proxy_user[i]     = 0;    /* Clean up password from memory */
  *conf->timeserver       = 0;
  return 1;
}