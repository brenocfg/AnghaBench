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
struct TYPE_4__ {char* alpn_string; char** alpn_list; int /*<<< orphan*/  alpn_status; } ;
struct TYPE_5__ {TYPE_1__ ssl_alpn; } ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ALPN_ENABLE ; 
 int ALPN_LIST_MAX ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,unsigned int) ; 
 char* ssl_mem_zalloc (unsigned int) ; 

int SSL_CTX_set_alpn_protos(SSL_CTX *ctx, const unsigned char *protos, unsigned protos_len)
{
     ctx->ssl_alpn.alpn_string = ssl_mem_zalloc(protos_len + 1);
     if (! ctx->ssl_alpn.alpn_string) {
	  return 1;
     }
     ctx->ssl_alpn.alpn_status = ALPN_ENABLE;
     memcpy(ctx->ssl_alpn.alpn_string, protos, protos_len);

     char *ptr = ctx->ssl_alpn.alpn_string;
     int i;
     /* Only running to 1 less than the actual size */
     for (i = 0; i < ALPN_LIST_MAX - 1; i++) {
	  char len = *ptr;
	  *ptr = '\0'; // Overwrite the length to act as previous element's string terminator
	  ptr++;
	  protos_len--;
	  ctx->ssl_alpn.alpn_list[i] = ptr;
	  ptr += len;
	  protos_len -= len;
	  if (! protos_len) {
	       i++;
	       break;
	  }
     }
     ctx->ssl_alpn.alpn_list[i] = NULL;
     return 0;
}