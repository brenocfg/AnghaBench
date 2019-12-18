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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int BUFFER_LEN ; 
 scalar_t__ buffer ; 
 int /*<<< orphan*/  macConvert32uto16s (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int write_pos ; 

__attribute__((used)) static void SNDMacUpdateAudio(u32 *left, u32 *right, u32 cnt) {
    u32 copy1size=0, copy2size=0;

    pthread_mutex_lock(&mutex);

    if((BUFFER_LEN - write_pos) < (cnt << 2)) {
        copy1size = (BUFFER_LEN - write_pos);
        copy2size = (cnt << 2) - copy1size;
    }
    else {
        copy1size = (cnt << 2);
        copy2size = 0;
    }

    macConvert32uto16s((s32 *)left, (s32 *)right,
                       (s16 *)(((u8 *)buffer) + write_pos),
                       copy1size >> 2);

    if(copy2size) {
        macConvert32uto16s((s32 *)left + (copy1size >> 2),
                           (s32 *)right + (copy1size >> 2),
                           (s16 *)buffer, copy2size >> 2);
    }

    write_pos += copy1size + copy2size;   
    write_pos %= (BUFFER_LEN);

    pthread_mutex_unlock(&mutex);
}