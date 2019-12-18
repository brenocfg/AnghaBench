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
struct TYPE_4__ {int /*<<< orphan*/  wdir; } ;
typedef  TYPE_1__ HB_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  _wrewinddir (int /*<<< orphan*/ ) ; 
 void rewinddir (TYPE_1__*) ; 

void hb_rewinddir(HB_DIR *dir)
{
#ifdef SYS_MINGW
    _wrewinddir(dir->wdir);
#else
    return rewinddir(dir);
#endif
}