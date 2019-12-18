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
struct TYPE_5__ {int rstate; } ;
struct TYPE_6__ {TYPE_1__ rlayer; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT2 (TYPE_2__*) ; 
#define  SSL_ST_READ_BODY 130 
#define  SSL_ST_READ_DONE 129 
#define  SSL_ST_READ_HEADER 128 

const char *SSL_rstate_string(SSL *ssl)
{
    const char *str;

    SSL_ASSERT2(ssl);

    switch (ssl->rlayer.rstate)
    {
        case SSL_ST_READ_HEADER:
            str = "RH";
            break;
        case SSL_ST_READ_BODY:
            str = "RB";
            break;
        case SSL_ST_READ_DONE:
            str = "RD";
            break;
        default:
            str = "unknown";
            break;
    }

    return str;
}