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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ mbedtls_asn1_named_data ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x509_write_extension (unsigned char**,unsigned char*,TYPE_1__*) ; 

int mbedtls_x509_write_extensions( unsigned char **p, unsigned char *start,
                           mbedtls_asn1_named_data *first )
{
    int ret;
    size_t len = 0;
    mbedtls_asn1_named_data *cur_ext = first;

    while( cur_ext != NULL )
    {
        MBEDTLS_ASN1_CHK_ADD( len, x509_write_extension( p, start, cur_ext ) );
        cur_ext = cur_ext->next;
    }

    return( (int) len );
}