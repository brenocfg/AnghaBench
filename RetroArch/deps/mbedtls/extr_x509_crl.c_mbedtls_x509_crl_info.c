#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  mon; int /*<<< orphan*/  year; } ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_12__ {struct TYPE_12__* next; TYPE_4__ revocation_date; int /*<<< orphan*/  serial; TYPE_3__ raw; } ;
typedef  TYPE_5__ mbedtls_x509_crl_entry ;
struct TYPE_9__ {int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  mon; int /*<<< orphan*/  year; } ;
struct TYPE_8__ {int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  mon; int /*<<< orphan*/  year; } ;
struct TYPE_13__ {int /*<<< orphan*/  sig_opts; int /*<<< orphan*/  sig_md; int /*<<< orphan*/  sig_pk; int /*<<< orphan*/  sig_oid; TYPE_5__ entry; TYPE_2__ next_update; TYPE_1__ this_update; int /*<<< orphan*/  issuer; int /*<<< orphan*/  version; } ;
typedef  TYPE_6__ mbedtls_x509_crl ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_X509_SAFE_SNPRINTF ; 
 int mbedtls_snprintf (char*,size_t,char*,...) ; 
 int mbedtls_x509_dn_gets (char*,size_t,int /*<<< orphan*/ *) ; 
 int mbedtls_x509_serial_gets (char*,size_t,int /*<<< orphan*/ *) ; 
 int mbedtls_x509_sig_alg_gets (char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mbedtls_x509_crl_info( char *buf, size_t size, const char *prefix,
                   const mbedtls_x509_crl *crl )
{
    int ret;
    size_t n;
    char *p;
    const mbedtls_x509_crl_entry *entry;

    p = buf;
    n = size;

    ret = mbedtls_snprintf( p, n, "%sCRL version   : %d",
                               prefix, crl->version );
    MBEDTLS_X509_SAFE_SNPRINTF;

    ret = mbedtls_snprintf( p, n, "\n%sissuer name   : ", prefix );
    MBEDTLS_X509_SAFE_SNPRINTF;
    ret = mbedtls_x509_dn_gets( p, n, &crl->issuer );
    MBEDTLS_X509_SAFE_SNPRINTF;

    ret = mbedtls_snprintf( p, n, "\n%sthis update   : " \
                   "%04d-%02d-%02d %02d:%02d:%02d", prefix,
                   crl->this_update.year, crl->this_update.mon,
                   crl->this_update.day,  crl->this_update.hour,
                   crl->this_update.min,  crl->this_update.sec );
    MBEDTLS_X509_SAFE_SNPRINTF;

    ret = mbedtls_snprintf( p, n, "\n%snext update   : " \
                   "%04d-%02d-%02d %02d:%02d:%02d", prefix,
                   crl->next_update.year, crl->next_update.mon,
                   crl->next_update.day,  crl->next_update.hour,
                   crl->next_update.min,  crl->next_update.sec );
    MBEDTLS_X509_SAFE_SNPRINTF;

    entry = &crl->entry;

    ret = mbedtls_snprintf( p, n, "\n%sRevoked certificates:",
                               prefix );
    MBEDTLS_X509_SAFE_SNPRINTF;

    while( entry != NULL && entry->raw.len != 0 )
    {
        ret = mbedtls_snprintf( p, n, "\n%sserial number: ",
                               prefix );
        MBEDTLS_X509_SAFE_SNPRINTF;

        ret = mbedtls_x509_serial_gets( p, n, &entry->serial );
        MBEDTLS_X509_SAFE_SNPRINTF;

        ret = mbedtls_snprintf( p, n, " revocation date: " \
                   "%04d-%02d-%02d %02d:%02d:%02d",
                   entry->revocation_date.year, entry->revocation_date.mon,
                   entry->revocation_date.day,  entry->revocation_date.hour,
                   entry->revocation_date.min,  entry->revocation_date.sec );
        MBEDTLS_X509_SAFE_SNPRINTF;

        entry = entry->next;
    }

    ret = mbedtls_snprintf( p, n, "\n%ssigned using  : ", prefix );
    MBEDTLS_X509_SAFE_SNPRINTF;

    ret = mbedtls_x509_sig_alg_gets( p, n, &crl->sig_oid, crl->sig_pk, crl->sig_md,
                             crl->sig_opts );
    MBEDTLS_X509_SAFE_SNPRINTF;

    ret = mbedtls_snprintf( p, n, "\n" );
    MBEDTLS_X509_SAFE_SNPRINTF;

    return( (int) ( size - n ) );
}