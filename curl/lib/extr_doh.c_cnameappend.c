#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cnamestore {char* alloc; size_t allocsize; size_t len; } ;
typedef  int /*<<< orphan*/  DOHcode ;

/* Variables and functions */
 int /*<<< orphan*/  DOH_OK ; 
 int /*<<< orphan*/  DOH_OUT_OF_MEM ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,size_t) ; 
 char* realloc (char*,size_t) ; 

__attribute__((used)) static DOHcode cnameappend(struct cnamestore *c,
                           unsigned char *src,
                           size_t len)
{
  if(!c->alloc) {
    c->allocsize = len + 1;
    c->alloc = malloc(c->allocsize);
    if(!c->alloc)
      return DOH_OUT_OF_MEM;
  }
  else if(c->allocsize < (c->allocsize + len + 1)) {
    char *ptr;
    c->allocsize += len + 1;
    ptr = realloc(c->alloc, c->allocsize);
    if(!ptr) {
      free(c->alloc);
      return DOH_OUT_OF_MEM;
    }
    c->alloc = ptr;
  }
  memcpy(&c->alloc[c->len], src, len);
  c->len += len;
  c->alloc[c->len] = 0; /* keep it zero terminated */
  return DOH_OK;
}