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
struct TYPE_5__ {int ext_types; int /*<<< orphan*/  ns_cert_type; int /*<<< orphan*/  subject_alt_names; int /*<<< orphan*/  ext_key_usage; int /*<<< orphan*/  key_usage; int /*<<< orphan*/  max_pathlen; int /*<<< orphan*/  ca_istrue; int /*<<< orphan*/  v3_ext; } ;
typedef  TYPE_1__ mbedtls_x509_crt ;
struct TYPE_6__ {unsigned char tag; size_t len; unsigned char* p; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ mbedtls_x509_buf ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_OCTET_STRING ; 
 int MBEDTLS_ASN1_OID ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_ASN1_OUT_OF_DATA ; 
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int MBEDTLS_ERR_X509_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_X509_INVALID_EXTENSIONS ; 
#define  MBEDTLS_X509_EXT_BASIC_CONSTRAINTS 132 
#define  MBEDTLS_X509_EXT_EXTENDED_KEY_USAGE 131 
#define  MBEDTLS_X509_EXT_KEY_USAGE 130 
#define  MBEDTLS_X509_EXT_NS_CERT_TYPE 129 
#define  MBEDTLS_X509_EXT_SUBJECT_ALT_NAME 128 
 int mbedtls_asn1_get_bool (unsigned char**,unsigned char*,int*) ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int) ; 
 int mbedtls_oid_get_x509_ext_type (TYPE_2__*,int*) ; 
 int mbedtls_x509_get_ext (unsigned char**,unsigned char const*,int /*<<< orphan*/ *,int) ; 
 int x509_get_basic_constraints (unsigned char**,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int x509_get_ext_key_usage (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 
 int x509_get_key_usage (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 
 int x509_get_ns_cert_type (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 
 int x509_get_subject_alt_name (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int x509_get_crt_ext( unsigned char **p,
                             const unsigned char *end,
                             mbedtls_x509_crt *crt )
{
    int ret;
    size_t len;
    unsigned char *end_ext_data, *end_ext_octet;

    if( ( ret = mbedtls_x509_get_ext( p, end, &crt->v3_ext, 3 ) ) != 0 )
    {
        if( ret == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
            return( 0 );

        return( ret );
    }

    while( *p < end )
    {
        /*
         * Extension  ::=  SEQUENCE  {
         *      extnID      OBJECT IDENTIFIER,
         *      critical    BOOLEAN DEFAULT FALSE,
         *      extnValue   OCTET STRING  }
         */
        mbedtls_x509_buf extn_oid = {0, 0, NULL};
        int is_critical = 0; /* DEFAULT FALSE */
        int ext_type = 0;

        if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
                MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        end_ext_data = *p + len;

        /* Get extension ID */
        extn_oid.tag = **p;

        if( ( ret = mbedtls_asn1_get_tag( p, end, &extn_oid.len, MBEDTLS_ASN1_OID ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        extn_oid.p = *p;
        *p += extn_oid.len;

        if( ( end - *p ) < 1 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_OUT_OF_DATA );

        /* Get optional critical */
        if( ( ret = mbedtls_asn1_get_bool( p, end_ext_data, &is_critical ) ) != 0 &&
            ( ret != MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ) )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        /* Data should be octet string type */
        if( ( ret = mbedtls_asn1_get_tag( p, end_ext_data, &len,
                MBEDTLS_ASN1_OCTET_STRING ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        end_ext_octet = *p + len;

        if( end_ext_octet != end_ext_data )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

        /*
         * Detect supported extensions
         */
        ret = mbedtls_oid_get_x509_ext_type( &extn_oid, &ext_type );

        if( ret != 0 )
        {
            /* No parser found, skip extension */
            *p = end_ext_octet;

#if !defined(MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION)
            if( is_critical )
            {
                /* Data is marked as critical: fail */
                return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                        MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );
            }
#endif
            continue;
        }

        /* Forbid repeated extensions */
        if( ( crt->ext_types & ext_type ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS );

        crt->ext_types |= ext_type;

        switch( ext_type )
        {
        case MBEDTLS_X509_EXT_BASIC_CONSTRAINTS:
            /* Parse basic constraints */
            if( ( ret = x509_get_basic_constraints( p, end_ext_octet,
                    &crt->ca_istrue, &crt->max_pathlen ) ) != 0 )
                return( ret );
            break;

        case MBEDTLS_X509_EXT_KEY_USAGE:
            /* Parse key usage */
            if( ( ret = x509_get_key_usage( p, end_ext_octet,
                    &crt->key_usage ) ) != 0 )
                return( ret );
            break;

        case MBEDTLS_X509_EXT_EXTENDED_KEY_USAGE:
            /* Parse extended key usage */
            if( ( ret = x509_get_ext_key_usage( p, end_ext_octet,
                    &crt->ext_key_usage ) ) != 0 )
                return( ret );
            break;

        case MBEDTLS_X509_EXT_SUBJECT_ALT_NAME:
            /* Parse subject alt name */
            if( ( ret = x509_get_subject_alt_name( p, end_ext_octet,
                    &crt->subject_alt_names ) ) != 0 )
                return( ret );
            break;

        case MBEDTLS_X509_EXT_NS_CERT_TYPE:
            /* Parse netscape certificate type */
            if( ( ret = x509_get_ns_cert_type( p, end_ext_octet,
                    &crt->ns_cert_type ) ) != 0 )
                return( ret );
            break;

        default:
            return( MBEDTLS_ERR_X509_FEATURE_UNAVAILABLE );
        }
    }

    if( *p != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}