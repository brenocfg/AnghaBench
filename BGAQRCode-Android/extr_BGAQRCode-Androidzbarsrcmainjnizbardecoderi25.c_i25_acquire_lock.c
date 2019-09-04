#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int character; int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {TYPE_1__ i25; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_2__ zbar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_I25 ; 
 scalar_t__ acquire_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int i25_acquire_lock (zbar_decoder_t *dcode)
{
    int i;
    /* lock shared resources */
    if(acquire_lock(dcode, ZBAR_I25)) {
        dcode->i25.character = -1;
        return(1);
    }

    /* copy holding buffer */
    for(i = 4; --i >= 0; )
        dcode->buf[i] = dcode->i25.buf[i];
    return(0);
}