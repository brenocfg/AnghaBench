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
typedef  scalar_t__ zbar_symbol_type_t ;
struct TYPE_3__ {scalar_t__ lock; } ;
typedef  TYPE_1__ zbar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbprintf (int,char*,scalar_t__) ; 

__attribute__((used)) static inline char acquire_lock (zbar_decoder_t *dcode,
                                 zbar_symbol_type_t req)
{
    if(dcode->lock) {
        dbprintf(2, " [locked %d]\n", dcode->lock);
        return(1);
    }
    dcode->lock = req;
    return(0);
}