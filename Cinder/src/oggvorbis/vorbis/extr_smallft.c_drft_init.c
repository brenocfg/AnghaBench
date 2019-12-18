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
struct TYPE_3__ {int n; void* splitcache; void* trigcache; } ;
typedef  TYPE_1__ drft_lookup ;

/* Variables and functions */
 void* _ogg_calloc (int,int) ; 
 int /*<<< orphan*/  fdrffti (int,void*,void*) ; 

void drft_init(drft_lookup *l,int n){
  l->n=n;
  l->trigcache=_ogg_calloc(3*n,sizeof(*l->trigcache));
  l->splitcache=_ogg_calloc(32,sizeof(*l->splitcache));
  fdrffti(n, l->trigcache, l->splitcache);
}