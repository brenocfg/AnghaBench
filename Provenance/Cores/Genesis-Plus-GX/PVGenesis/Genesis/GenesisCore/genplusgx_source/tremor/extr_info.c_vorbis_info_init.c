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
struct TYPE_4__ {int /*<<< orphan*/ * codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
typedef  int /*<<< orphan*/  codec_setup_info ;

/* Variables and functions */
 scalar_t__ _ogg_calloc (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void vorbis_info_init(vorbis_info *vi){
  memset(vi,0,sizeof(*vi));
  vi->codec_setup=(codec_setup_info *)_ogg_calloc(1,sizeof(codec_setup_info));
}