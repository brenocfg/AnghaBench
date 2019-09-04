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
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_6__ {int character; } ;
struct TYPE_5__ {TYPE_2__ code93; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code93_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_CODE93 ; 
 int /*<<< orphan*/  ZBAR_NONE ; 
 int /*<<< orphan*/  dbprintf (int,char*,char const*) ; 
 int /*<<< orphan*/  release_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zbar_symbol_type_t
decode_abort (zbar_decoder_t *dcode,
              const char *reason)
{
    code93_decoder_t *dcode93 = &dcode->code93;
    if(dcode93->character > 1)
        release_lock(dcode, ZBAR_CODE93);
    dcode93->character = -1;
    if(reason)
        dbprintf(1, " [%s]\n", reason);
    return(ZBAR_NONE);
}