#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_x509_buf ;
typedef  scalar_t__ mbedtls_pk_type_t ;
struct TYPE_2__ {int /*<<< orphan*/  expected_salt_len; scalar_t__ mgf1_hash_id; } ;
typedef  TYPE_1__ mbedtls_pk_rsassa_pss_options ;
typedef  scalar_t__ mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_md_info_t ;

/* Variables and functions */
 scalar_t__ MBEDTLS_PK_RSASSA_PSS ; 
 int /*<<< orphan*/  MBEDTLS_X509_SAFE_SNPRINTF ; 
 char* mbedtls_md_get_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * mbedtls_md_info_from_type (scalar_t__) ; 
 int mbedtls_oid_get_sig_alg_desc (int /*<<< orphan*/  const*,char const**) ; 
 int mbedtls_snprintf (char*,size_t,char*,...) ; 

int mbedtls_x509_sig_alg_gets( char *buf, size_t size, const mbedtls_x509_buf *sig_oid,
                       mbedtls_pk_type_t pk_alg, mbedtls_md_type_t md_alg,
                       const void *sig_opts )
{
    int ret;
    char *p = buf;
    size_t n = size;
    const char *desc = NULL;

    ret = mbedtls_oid_get_sig_alg_desc( sig_oid, &desc );
    if( ret != 0 )
        ret = mbedtls_snprintf( p, n, "???"  );
    else
        ret = mbedtls_snprintf( p, n, "%s", desc );
    MBEDTLS_X509_SAFE_SNPRINTF;

#if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT)
    if( pk_alg == MBEDTLS_PK_RSASSA_PSS )
    {
        const mbedtls_pk_rsassa_pss_options *pss_opts;
        const mbedtls_md_info_t *md_info, *mgf_md_info;

        pss_opts = (const mbedtls_pk_rsassa_pss_options *) sig_opts;

        md_info = mbedtls_md_info_from_type( md_alg );
        mgf_md_info = mbedtls_md_info_from_type( pss_opts->mgf1_hash_id );

        ret = mbedtls_snprintf( p, n, " (%s, MGF1-%s, 0x%02X)",
                              md_info ? mbedtls_md_get_name( md_info ) : "???",
                              mgf_md_info ? mbedtls_md_get_name( mgf_md_info ) : "???",
                              pss_opts->expected_salt_len );
        MBEDTLS_X509_SAFE_SNPRINTF;
    }
#else
    ((void) pk_alg);
    ((void) md_alg);
    ((void) sig_opts);
#endif /* MBEDTLS_X509_RSASSA_PSS_SUPPORT */

    return( (int)( size - n ) );
}