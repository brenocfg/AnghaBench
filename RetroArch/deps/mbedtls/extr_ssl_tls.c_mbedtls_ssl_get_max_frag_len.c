#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* session_out; TYPE_1__* conf; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_6__ {size_t mfl_code; } ;
struct TYPE_5__ {size_t mfl_code; } ;

/* Variables and functions */
 size_t* mfl_code_to_length ; 

size_t mbedtls_ssl_get_max_frag_len( const mbedtls_ssl_context *ssl )
{
    size_t max_len;

    /*
     * Assume mfl_code is correct since it was checked when set
     */
    max_len = mfl_code_to_length[ssl->conf->mfl_code];

    /*
     * Check if a smaller max length was negotiated
     */
    if( ssl->session_out != NULL &&
        mfl_code_to_length[ssl->session_out->mfl_code] < max_len )
    {
        max_len = mfl_code_to_length[ssl->session_out->mfl_code];
    }

    return max_len;
}