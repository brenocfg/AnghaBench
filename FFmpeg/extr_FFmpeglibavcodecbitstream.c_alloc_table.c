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
typedef  int /*<<< orphan*/  VLC_TYPE ;
struct TYPE_3__ {int table_size; int table_allocated; int bits; scalar_t__ table; } ;
typedef  TYPE_1__ VLC ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ av_realloc_f (scalar_t__,int,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alloc_table(VLC *vlc, int size, int use_static)
{
    int index = vlc->table_size;

    vlc->table_size += size;
    if (vlc->table_size > vlc->table_allocated) {
        if (use_static)
            abort(); // cannot do anything, init_vlc() is used with too little memory
        vlc->table_allocated += (1 << vlc->bits);
        vlc->table = av_realloc_f(vlc->table, vlc->table_allocated, sizeof(VLC_TYPE) * 2);
        if (!vlc->table) {
            vlc->table_allocated = 0;
            vlc->table_size = 0;
            return AVERROR(ENOMEM);
        }
        memset(vlc->table + vlc->table_allocated - (1 << vlc->bits), 0, sizeof(VLC_TYPE) * 2 << vlc->bits);
    }
    return index;
}