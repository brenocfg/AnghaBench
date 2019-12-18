#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int mbedtls_cipher_padding_t ;
struct TYPE_5__ {int /*<<< orphan*/  get_padding; int /*<<< orphan*/ * add_padding; TYPE_1__* cipher_info; } ;
typedef  TYPE_2__ mbedtls_cipher_context_t ;
struct TYPE_4__ {scalar_t__ mode; } ;

/* Variables and functions */
 int MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE ; 
 scalar_t__ MBEDTLS_MODE_CBC ; 
#define  MBEDTLS_PADDING_NONE 132 
#define  MBEDTLS_PADDING_ONE_AND_ZEROS 131 
#define  MBEDTLS_PADDING_PKCS7 130 
#define  MBEDTLS_PADDING_ZEROS 129 
#define  MBEDTLS_PADDING_ZEROS_AND_LEN 128 
 int /*<<< orphan*/ * add_one_and_zeros_padding ; 
 int /*<<< orphan*/ * add_pkcs_padding ; 
 int /*<<< orphan*/ * add_zeros_and_len_padding ; 
 int /*<<< orphan*/ * add_zeros_padding ; 
 int /*<<< orphan*/  get_no_padding ; 
 int /*<<< orphan*/  get_one_and_zeros_padding ; 
 int /*<<< orphan*/  get_pkcs_padding ; 
 int /*<<< orphan*/  get_zeros_and_len_padding ; 
 int /*<<< orphan*/  get_zeros_padding ; 

int mbedtls_cipher_set_padding_mode( mbedtls_cipher_context_t *ctx, mbedtls_cipher_padding_t mode )
{
    if( NULL == ctx ||
        MBEDTLS_MODE_CBC != ctx->cipher_info->mode )
    {
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );
    }

    switch( mode )
    {
#if defined(MBEDTLS_CIPHER_PADDING_PKCS7)
    case MBEDTLS_PADDING_PKCS7:
        ctx->add_padding = add_pkcs_padding;
        ctx->get_padding = get_pkcs_padding;
        break;
#endif
#if defined(MBEDTLS_CIPHER_PADDING_ONE_AND_ZEROS)
    case MBEDTLS_PADDING_ONE_AND_ZEROS:
        ctx->add_padding = add_one_and_zeros_padding;
        ctx->get_padding = get_one_and_zeros_padding;
        break;
#endif
#if defined(MBEDTLS_CIPHER_PADDING_ZEROS_AND_LEN)
    case MBEDTLS_PADDING_ZEROS_AND_LEN:
        ctx->add_padding = add_zeros_and_len_padding;
        ctx->get_padding = get_zeros_and_len_padding;
        break;
#endif
#if defined(MBEDTLS_CIPHER_PADDING_ZEROS)
    case MBEDTLS_PADDING_ZEROS:
        ctx->add_padding = add_zeros_padding;
        ctx->get_padding = get_zeros_padding;
        break;
#endif
    case MBEDTLS_PADDING_NONE:
        ctx->add_padding = NULL;
        ctx->get_padding = get_no_padding;
        break;

    default:
        return( MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE );
    }

    return( 0 );
}