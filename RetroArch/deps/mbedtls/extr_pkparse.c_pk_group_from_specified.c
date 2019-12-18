#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_7__ {int /*<<< orphan*/  N; void* nbits; TYPE_6__ G; int /*<<< orphan*/  P; int /*<<< orphan*/  B; int /*<<< orphan*/  A; void* pbits; } ;
typedef  TYPE_1__ mbedtls_ecp_group ;
struct TYPE_8__ {unsigned char* p; size_t len; } ;
typedef  TYPE_2__ mbedtls_asn1_buf ;

/* Variables and functions */
 int MBEDTLS_ASN1_BIT_STRING ; 
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_OCTET_STRING ; 
 int MBEDTLS_ASN1_OID ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_PK_KEY_INVALID_FORMAT ; 
 int /*<<< orphan*/  MBEDTLS_OID_ANSI_X9_62_PRIME_FIELD ; 
 size_t MBEDTLS_OID_SIZE (int /*<<< orphan*/ ) ; 
 int mbedtls_asn1_get_int (unsigned char**,unsigned char const* const,int*) ; 
 int mbedtls_asn1_get_mpi (unsigned char**,unsigned char const* const,int /*<<< orphan*/ *) ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const* const,size_t*,int) ; 
 int mbedtls_ecp_point_read_binary (TYPE_1__*,TYPE_6__*,unsigned char const*,size_t) ; 
 void* mbedtls_mpi_bitlen (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 
 int mbedtls_mpi_read_binary (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int mbedtls_mpi_size (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int pk_group_from_specified( const mbedtls_asn1_buf *params, mbedtls_ecp_group *grp )
{
    int ret;
    unsigned char *p = params->p;
    const unsigned char * const end = params->p + params->len;
    const unsigned char *end_field, *end_curve;
    size_t len;
    int ver;

    /* SpecifiedECDomainVersion ::= INTEGER { 1, 2, 3 } */
    if( ( ret = mbedtls_asn1_get_int( &p, end, &ver ) ) != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );

    if( ver < 1 || ver > 3 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT );

    /*
     * FieldID { FIELD-ID:IOSet } ::= SEQUENCE { -- Finite field
     *       fieldType FIELD-ID.&id({IOSet}),
     *       parameters FIELD-ID.&Type({IOSet}{@fieldType})
     * }
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( ret );

    end_field = p + len;

    /*
     * FIELD-ID ::= TYPE-IDENTIFIER
     * FieldTypes FIELD-ID ::= {
     *       { Prime-p IDENTIFIED BY prime-field } |
     *       { Characteristic-two IDENTIFIED BY characteristic-two-field }
     * }
     * prime-field OBJECT IDENTIFIER ::= { id-fieldType 1 }
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end_field, &len, MBEDTLS_ASN1_OID ) ) != 0 )
        return( ret );

    if( len != MBEDTLS_OID_SIZE( MBEDTLS_OID_ANSI_X9_62_PRIME_FIELD ) ||
        memcmp( p, MBEDTLS_OID_ANSI_X9_62_PRIME_FIELD, len ) != 0 )
    {
        return( MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE );
    }

    p += len;

    /* Prime-p ::= INTEGER -- Field of size p. */
    if( ( ret = mbedtls_asn1_get_mpi( &p, end_field, &grp->P ) ) != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );

    grp->pbits = mbedtls_mpi_bitlen( &grp->P );

    if( p != end_field )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    /*
     * Curve ::= SEQUENCE {
     *       a FieldElement,
     *       b FieldElement,
     *       seed BIT STRING OPTIONAL
     *       -- Shall be present if used in SpecifiedECDomain
     *       -- with version equal to ecdpVer2 or ecdpVer3
     * }
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( ret );

    end_curve = p + len;

    /*
     * FieldElement ::= OCTET STRING
     * containing an integer in the case of a prime field
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end_curve, &len, MBEDTLS_ASN1_OCTET_STRING ) ) != 0 ||
        ( ret = mbedtls_mpi_read_binary( &grp->A, p, len ) ) != 0 )
    {
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );
    }

    p += len;

    if( ( ret = mbedtls_asn1_get_tag( &p, end_curve, &len, MBEDTLS_ASN1_OCTET_STRING ) ) != 0 ||
        ( ret = mbedtls_mpi_read_binary( &grp->B, p, len ) ) != 0 )
    {
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );
    }

    p += len;

    /* Ignore seed BIT STRING OPTIONAL */
    if( ( ret = mbedtls_asn1_get_tag( &p, end_curve, &len, MBEDTLS_ASN1_BIT_STRING ) ) == 0 )
        p += len;

    if( p != end_curve )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    /*
     * ECPoint ::= OCTET STRING
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len, MBEDTLS_ASN1_OCTET_STRING ) ) != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );

    if( ( ret = mbedtls_ecp_point_read_binary( grp, &grp->G,
                                      ( const unsigned char *) p, len ) ) != 0 )
    {
        /*
         * If we can't read the point because it's compressed, cheat by
         * reading only the X coordinate and the parity bit of Y.
         */
        if( ret != MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE ||
            ( p[0] != 0x02 && p[0] != 0x03 ) ||
            len != mbedtls_mpi_size( &grp->P ) + 1 ||
            mbedtls_mpi_read_binary( &grp->G.X, p + 1, len - 1 ) != 0 ||
            mbedtls_mpi_lset( &grp->G.Y, p[0] - 2 ) != 0 ||
            mbedtls_mpi_lset( &grp->G.Z, 1 ) != 0 )
        {
            return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT );
        }
    }

    p += len;

    /*
     * order INTEGER
     */
    if( ( ret = mbedtls_asn1_get_mpi( &p, end, &grp->N ) ) != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );

    grp->nbits = mbedtls_mpi_bitlen( &grp->N );

    /*
     * Allow optional elements by purposefully not enforcing p == end here.
     */

    return( 0 );
}