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
struct TYPE_4__ {struct TYPE_4__* lsp_look; struct TYPE_4__* linearmap; } ;
typedef  TYPE_1__ vorbis_look_floor0 ;
typedef  int /*<<< orphan*/  vorbis_look_floor ;

/* Variables and functions */
 int /*<<< orphan*/  _ogg_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void floor0_free_look(vorbis_look_floor *i){
  vorbis_look_floor0 *look=(vorbis_look_floor0 *)i;
  if(look){

    if(look->linearmap)_ogg_free(look->linearmap);
    if(look->lsp_look)_ogg_free(look->lsp_look);
    memset(look,0,sizeof(*look));
    _ogg_free(look);
  }
}