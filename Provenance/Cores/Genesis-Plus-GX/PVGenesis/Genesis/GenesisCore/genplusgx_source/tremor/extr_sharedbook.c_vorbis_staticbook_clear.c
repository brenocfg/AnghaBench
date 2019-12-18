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
struct TYPE_4__ {scalar_t__ lengthlist; scalar_t__ quantlist; } ;
typedef  TYPE_1__ static_codebook ;

/* Variables and functions */
 int /*<<< orphan*/  _ogg_free (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void vorbis_staticbook_clear(static_codebook *b){
  if(b->quantlist)_ogg_free(b->quantlist);
  if(b->lengthlist)_ogg_free(b->lengthlist);
  memset(b,0,sizeof(*b));

}