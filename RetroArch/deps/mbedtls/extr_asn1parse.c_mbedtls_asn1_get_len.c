#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int MBEDTLS_ERR_ASN1_INVALID_LENGTH ; 
 int MBEDTLS_ERR_ASN1_OUT_OF_DATA ; 

int mbedtls_asn1_get_len( unsigned char **p,
                  const unsigned char *end,
                  size_t *len )
{
    if( ( end - *p ) < 1 )
        return( MBEDTLS_ERR_ASN1_OUT_OF_DATA );

    if( ( **p & 0x80 ) == 0 )
        *len = *(*p)++;
    else
    {
        switch( **p & 0x7F )
        {
        case 1:
            if( ( end - *p ) < 2 )
                return( MBEDTLS_ERR_ASN1_OUT_OF_DATA );

            *len = (*p)[1];
            (*p) += 2;
            break;

        case 2:
            if( ( end - *p ) < 3 )
                return( MBEDTLS_ERR_ASN1_OUT_OF_DATA );

            *len = ( (size_t)(*p)[1] << 8 ) | (*p)[2];
            (*p) += 3;
            break;

        case 3:
            if( ( end - *p ) < 4 )
                return( MBEDTLS_ERR_ASN1_OUT_OF_DATA );

            *len = ( (size_t)(*p)[1] << 16 ) |
                   ( (size_t)(*p)[2] << 8  ) | (*p)[3];
            (*p) += 4;
            break;

        case 4:
            if( ( end - *p ) < 5 )
                return( MBEDTLS_ERR_ASN1_OUT_OF_DATA );

            *len = ( (size_t)(*p)[1] << 24 ) | ( (size_t)(*p)[2] << 16 ) |
                   ( (size_t)(*p)[3] << 8  ) |           (*p)[4];
            (*p) += 5;
            break;

        default:
            return( MBEDTLS_ERR_ASN1_INVALID_LENGTH );
        }
    }

    if( *len > (size_t) ( end - *p ) )
        return( MBEDTLS_ERR_ASN1_OUT_OF_DATA );

    return( 0 );
}