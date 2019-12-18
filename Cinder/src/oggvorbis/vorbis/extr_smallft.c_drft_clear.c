#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ splitcache; scalar_t__ trigcache; } ;
typedef  TYPE_1__ drft_lookup ;

/* Variables and functions */
 int /*<<< orphan*/  _ogg_free (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void drft_clear(drft_lookup *l){
  if(l){
    if(l->trigcache)_ogg_free(l->trigcache);
    if(l->splitcache)_ogg_free(l->splitcache);
    memset(l,0,sizeof(*l));
  }
}