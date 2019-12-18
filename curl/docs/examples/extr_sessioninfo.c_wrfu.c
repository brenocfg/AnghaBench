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
struct curl_tlssessioninfo {int backend; int /*<<< orphan*/  internals; } ;
typedef  int /*<<< orphan*/  gnutls_x509_crt_t ;
struct TYPE_5__ {char* size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ gnutls_datum_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLINFO_TLS_SESSION ; 
#define  CURLSSLBACKEND_GNUTLS 129 
#define  CURLSSLBACKEND_NONE 128 
 int /*<<< orphan*/  GNUTLS_CRT_PRINT_FULL ; 
 int /*<<< orphan*/  GNUTLS_E_SUCCESS ; 
 int /*<<< orphan*/  GNUTLS_X509_FMT_DER ; 
 int /*<<< orphan*/  curl ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct curl_tlssessioninfo const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* gnutls_certificate_get_peers (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  gnutls_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_x509_crt_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_x509_crt_import (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_x509_crt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnutls_x509_crt_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static size_t wrfu(void *ptr, size_t size, size_t nmemb, void *stream)
{
  const struct curl_tlssessioninfo *info;
  unsigned int cert_list_size;
  const gnutls_datum_t *chainp;
  CURLcode res;

  (void)stream;
  (void)ptr;

  res = curl_easy_getinfo(curl, CURLINFO_TLS_SESSION, &info);

  if(!res) {
    switch(info->backend) {
    case CURLSSLBACKEND_GNUTLS:
      /* info->internals is now the gnutls_session_t */
      chainp = gnutls_certificate_get_peers(info->internals, &cert_list_size);
      if((chainp) && (cert_list_size)) {
        unsigned int i;

        for(i = 0; i < cert_list_size; i++) {
          gnutls_x509_crt_t cert;
          gnutls_datum_t dn;

          if(GNUTLS_E_SUCCESS == gnutls_x509_crt_init(&cert)) {
            if(GNUTLS_E_SUCCESS ==
               gnutls_x509_crt_import(cert, &chainp[i], GNUTLS_X509_FMT_DER)) {
              if(GNUTLS_E_SUCCESS ==
                 gnutls_x509_crt_print(cert, GNUTLS_CRT_PRINT_FULL, &dn)) {
                fprintf(stderr, "Certificate #%u: %.*s", i, dn.size, dn.data);

                gnutls_free(dn.data);
              }
            }

            gnutls_x509_crt_deinit(cert);
          }
        }
      }
      break;
    case CURLSSLBACKEND_NONE:
    default:
      break;
    }
  }

  return size * nmemb;
}