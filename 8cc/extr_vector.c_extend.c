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
struct TYPE_3__ {int len; int nalloc; void* body; } ;
typedef  TYPE_1__ Vector ;

/* Variables and functions */
 int /*<<< orphan*/  MIN_SIZE ; 
 void* malloc (int) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  roundup (int) ; 

__attribute__((used)) static void extend(Vector *vec, int delta) {
    if (vec->len + delta <= vec->nalloc)
        return;
    int nelem = max(roundup(vec->len + delta), MIN_SIZE);
    void *newbody = malloc(sizeof(void *) * nelem);
    memcpy(newbody, vec->body, sizeof(void *) * vec->len);
    vec->body = newbody;
    vec->nalloc = nelem;
}