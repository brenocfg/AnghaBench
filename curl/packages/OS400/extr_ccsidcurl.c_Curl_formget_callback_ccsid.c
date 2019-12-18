#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t (* append ) (int /*<<< orphan*/ ,char const*,size_t) ;int /*<<< orphan*/  arg; int /*<<< orphan*/  ccsid; } ;
typedef  TYPE_1__ cfcdata ;

/* Variables and functions */
 int /*<<< orphan*/  ASCII_CCSID ; 
 size_t MAX_CONV_EXPANSION ; 
 int convert (char*,size_t,int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 size_t stub1 (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t stub2 (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static size_t
Curl_formget_callback_ccsid(void *arg, const char *buf, size_t len)

{
  cfcdata * p;
  char *b;
  int l;
  size_t ret;

  p = (cfcdata *) arg;

  if((long) len <= 0)
    return (*p->append)(p->arg, buf, len);

  b = malloc(MAX_CONV_EXPANSION * len);

  if(!b)
    return (size_t) -1;

  l = convert(b, MAX_CONV_EXPANSION * len, p->ccsid, buf, len, ASCII_CCSID);

  if(l < 0) {
    free(b);
    return (size_t) -1;
    }

  ret = (*p->append)(p->arg, b, l);
  free(b);
  return ret == l? len: -1;
}