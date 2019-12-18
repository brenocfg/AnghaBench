#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ mbedtls_asn1_named_data ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_asn1_free_named_data (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_free (TYPE_1__*) ; 

void mbedtls_asn1_free_named_data_list( mbedtls_asn1_named_data **head )
{
    mbedtls_asn1_named_data *cur;

    while( ( cur = *head ) != NULL )
    {
        *head = cur->next;
        mbedtls_asn1_free_named_data( cur );
        mbedtls_free( cur );
    }
}