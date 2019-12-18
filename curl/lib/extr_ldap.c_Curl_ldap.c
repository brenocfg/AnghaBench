#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int timeval ;
struct TYPE_21__ {char* name; int /*<<< orphan*/  dispname; } ;
struct TYPE_18__ {char* CAfile; scalar_t__ verifypeer; } ;
struct TYPE_17__ {scalar_t__ user_passwd; } ;
struct connectdata {char* user; char* passwd; scalar_t__ port; TYPE_7__ host; TYPE_4__ ssl_config; TYPE_3__ bits; TYPE_2__* given; struct Curl_easy* data; } ;
struct TYPE_19__ {scalar_t__ cert_type; } ;
struct TYPE_20__ {TYPE_5__ ssl; } ;
struct TYPE_15__ {int url; } ;
struct Curl_easy {TYPE_6__ set; TYPE_1__ change; } ;
typedef  scalar_t__ curl_off_t ;
struct TYPE_23__ {char* bv_val; int bv_len; } ;
struct TYPE_22__ {int /*<<< orphan*/  lud_attrs; int /*<<< orphan*/  lud_filter; int /*<<< orphan*/  lud_scope; int /*<<< orphan*/  lud_dn; } ;
struct TYPE_16__ {int flags; } ;
typedef  char TCHAR ;
typedef  TYPE_8__ LDAPURLDesc ;
typedef  int /*<<< orphan*/  LDAPMessage ;
typedef  int /*<<< orphan*/  LDAP ;
typedef  scalar_t__ CURLcode ;
typedef  TYPE_9__ BerValue ;
typedef  int /*<<< orphan*/  BerElement ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENTWRITE_BODY ; 
 scalar_t__ CURLE_COULDNT_CONNECT ; 
 scalar_t__ CURLE_LDAP_CANNOT_BIND ; 
 scalar_t__ CURLE_LDAP_INVALID_URL ; 
 scalar_t__ CURLE_LDAP_SEARCH_FAILED ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_SSL_CERTPROBLEM ; 
 scalar_t__ Curl_base64_encode (struct Curl_easy*,char*,int,char**,size_t*) ; 
 scalar_t__ Curl_client_write (struct connectdata*,int /*<<< orphan*/ ,char*,int) ; 
 char* Curl_convert_UTF8_to_tchar (char*) ; 
 char* Curl_convert_tchar_to_UTF8 (char*) ; 
 int /*<<< orphan*/  Curl_pgrsSetDownloadCounter (struct Curl_easy*,scalar_t__) ; 
 int /*<<< orphan*/  Curl_setup_transfer (struct Curl_easy*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Curl_unicodefree (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int LDAPSSL_CERT_FILETYPE_B64 ; 
 int LDAPSSL_CERT_FILETYPE_DER ; 
 int LDAPSSL_VERIFY_NONE ; 
 int LDAPSSL_VERIFY_SERVER ; 
 int /*<<< orphan*/  LDAP_OPT_NETWORK_TIMEOUT ; 
 int* LDAP_OPT_ON ; 
 int /*<<< orphan*/  LDAP_OPT_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  LDAP_OPT_SSL ; 
 int /*<<< orphan*/  LDAP_OPT_X_TLS ; 
 int /*<<< orphan*/  LDAP_OPT_X_TLS_CACERTFILE ; 
 int LDAP_OPT_X_TLS_DEMAND ; 
 int LDAP_OPT_X_TLS_HARD ; 
 int LDAP_OPT_X_TLS_NEVER ; 
 int /*<<< orphan*/  LDAP_OPT_X_TLS_REQUIRE_CERT ; 
 int LDAP_SIZELIMIT_EXCEEDED ; 
 int LDAP_SUCCESS ; 
 int /*<<< orphan*/  LDAP_TRACE (char*) ; 
 int /*<<< orphan*/  LDAP_VENDOR_NAME ; 
 int /*<<< orphan*/  LDAP_VENDOR_VERSION ; 
 int LDAP_VERSION2 ; 
 int LDAP_VERSION3 ; 
 int PROTOPT_SSL ; 
 int TRUE ; 
 int _ldap_url_parse (struct connectdata*,TYPE_8__**) ; 
 int /*<<< orphan*/  ber_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connclose (struct connectdata*,char*) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 
 char* ldap_err2string (int) ; 
 char* ldap_first_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * ldap_first_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_free_urldesc (TYPE_8__*) ; 
 char* ldap_get_dn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_9__** ldap_get_values_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ldap_init (char*,int) ; 
 int /*<<< orphan*/  ldap_memfree (char*) ; 
 int /*<<< orphan*/  ldap_msgfree (int /*<<< orphan*/ *) ; 
 char* ldap_next_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldap_next_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ldap_search_s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int ldap_set_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int ldap_simple_bind_s (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * ldap_sslinit (char*,int,int) ; 
 int /*<<< orphan*/  ldap_unbind_s (int /*<<< orphan*/ *) ; 
 int ldap_url_parse (int,TYPE_8__**) ; 
 int /*<<< orphan*/  ldap_value_free_len (TYPE_9__**) ; 
 int ldap_win_bind (struct connectdata*,int /*<<< orphan*/ *,char*,char*) ; 
 int ldapssl_add_trusted_cert (char*,int) ; 
 int /*<<< orphan*/  ldapssl_client_deinit () ; 
 int ldapssl_client_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldapssl_init (char*,int,int) ; 
 int ldapssl_set_verify_mode (int) ; 
 scalar_t__ strcasecompare (scalar_t__,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static CURLcode Curl_ldap(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  int rc = 0;
  LDAP *server = NULL;
  LDAPURLDesc *ludp = NULL;
  LDAPMessage *ldapmsg = NULL;
  LDAPMessage *entryIterator;
  int num = 0;
  struct Curl_easy *data = conn->data;
  int ldap_proto = LDAP_VERSION3;
  int ldap_ssl = 0;
  char *val_b64 = NULL;
  size_t val_b64_sz = 0;
  curl_off_t dlsize = 0;
#ifdef LDAP_OPT_NETWORK_TIMEOUT
  struct timeval ldap_timeout = {10, 0}; /* 10 sec connection/search timeout */
#endif
#if defined(USE_WIN32_LDAP)
  TCHAR *host = NULL;
#else
  char *host = NULL;
#endif
  char *user = NULL;
  char *passwd = NULL;

  *done = TRUE; /* unconditionally */
  infof(data, "LDAP local: LDAP Vendor = %s ; LDAP Version = %d\n",
          LDAP_VENDOR_NAME, LDAP_VENDOR_VERSION);
  infof(data, "LDAP local: %s\n", data->change.url);

#ifdef HAVE_LDAP_URL_PARSE
  rc = ldap_url_parse(data->change.url, &ludp);
#else
  rc = _ldap_url_parse(conn, &ludp);
#endif
  if(rc != 0) {
    failf(data, "LDAP local: %s", ldap_err2string(rc));
    result = CURLE_LDAP_INVALID_URL;
    goto quit;
  }

  /* Get the URL scheme (either ldap or ldaps) */
  if(conn->given->flags & PROTOPT_SSL)
    ldap_ssl = 1;
  infof(data, "LDAP local: trying to establish %s connection\n",
          ldap_ssl ? "encrypted" : "cleartext");

#if defined(USE_WIN32_LDAP)
  host = Curl_convert_UTF8_to_tchar(conn->host.name);
  if(!host) {
    result = CURLE_OUT_OF_MEMORY;

    goto quit;
  }
#else
  host = conn->host.name;
#endif

  if(conn->bits.user_passwd) {
    user = conn->user;
    passwd = conn->passwd;
  }

#ifdef LDAP_OPT_NETWORK_TIMEOUT
  ldap_set_option(NULL, LDAP_OPT_NETWORK_TIMEOUT, &ldap_timeout);
#endif
  ldap_set_option(NULL, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);

  if(ldap_ssl) {
#ifdef HAVE_LDAP_SSL
#ifdef USE_WIN32_LDAP
    /* Win32 LDAP SDK doesn't support insecure mode without CA! */
    server = ldap_sslinit(host, (int)conn->port, 1);
    ldap_set_option(server, LDAP_OPT_SSL, LDAP_OPT_ON);
#else
    int ldap_option;
    char *ldap_ca = conn->ssl_config.CAfile;
#if defined(CURL_HAS_NOVELL_LDAPSDK)
    rc = ldapssl_client_init(NULL, NULL);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ldapssl_client_init %s", ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
    if(conn->ssl_config.verifypeer) {
      /* Novell SDK supports DER or BASE64 files. */
      int cert_type = LDAPSSL_CERT_FILETYPE_B64;
      if((data->set.ssl.cert_type) &&
         (strcasecompare(data->set.ssl.cert_type, "DER")))
        cert_type = LDAPSSL_CERT_FILETYPE_DER;
      if(!ldap_ca) {
        failf(data, "LDAP local: ERROR %s CA cert not set!",
              (cert_type == LDAPSSL_CERT_FILETYPE_DER ? "DER" : "PEM"));
        result = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      infof(data, "LDAP local: using %s CA cert '%s'\n",
              (cert_type == LDAPSSL_CERT_FILETYPE_DER ? "DER" : "PEM"),
              ldap_ca);
      rc = ldapssl_add_trusted_cert(ldap_ca, cert_type);
      if(rc != LDAP_SUCCESS) {
        failf(data, "LDAP local: ERROR setting %s CA cert: %s",
                (cert_type == LDAPSSL_CERT_FILETYPE_DER ? "DER" : "PEM"),
                ldap_err2string(rc));
        result = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      ldap_option = LDAPSSL_VERIFY_SERVER;
    }
    else
      ldap_option = LDAPSSL_VERIFY_NONE;
    rc = ldapssl_set_verify_mode(ldap_option);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR setting cert verify mode: %s",
              ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
    server = ldapssl_init(host, (int)conn->port, 1);
    if(server == NULL) {
      failf(data, "LDAP local: Cannot connect to %s:%ld",
            conn->host.dispname, conn->port);
      result = CURLE_COULDNT_CONNECT;
      goto quit;
    }
#elif defined(LDAP_OPT_X_TLS)
    if(conn->ssl_config.verifypeer) {
      /* OpenLDAP SDK supports BASE64 files. */
      if((data->set.ssl.cert_type) &&
         (!strcasecompare(data->set.ssl.cert_type, "PEM"))) {
        failf(data, "LDAP local: ERROR OpenLDAP only supports PEM cert-type!");
        result = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      if(!ldap_ca) {
        failf(data, "LDAP local: ERROR PEM CA cert not set!");
        result = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      infof(data, "LDAP local: using PEM CA cert: %s\n", ldap_ca);
      rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_CACERTFILE, ldap_ca);
      if(rc != LDAP_SUCCESS) {
        failf(data, "LDAP local: ERROR setting PEM CA cert: %s",
                ldap_err2string(rc));
        result = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      ldap_option = LDAP_OPT_X_TLS_DEMAND;
    }
    else
      ldap_option = LDAP_OPT_X_TLS_NEVER;

    rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &ldap_option);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR setting cert verify mode: %s",
              ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
    server = ldap_init(host, (int)conn->port);
    if(server == NULL) {
      failf(data, "LDAP local: Cannot connect to %s:%ld",
            conn->host.dispname, conn->port);
      result = CURLE_COULDNT_CONNECT;
      goto quit;
    }
    ldap_option = LDAP_OPT_X_TLS_HARD;
    rc = ldap_set_option(server, LDAP_OPT_X_TLS, &ldap_option);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR setting SSL/TLS mode: %s",
              ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
/*
    rc = ldap_start_tls_s(server, NULL, NULL);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR starting SSL/TLS mode: %s",
              ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
*/
#else
    /* we should probably never come up to here since configure
       should check in first place if we can support LDAP SSL/TLS */
    failf(data, "LDAP local: SSL/TLS not supported with this version "
            "of the OpenLDAP toolkit\n");
    result = CURLE_SSL_CERTPROBLEM;
    goto quit;
#endif
#endif
#endif /* CURL_LDAP_USE_SSL */
  }
  else {
    server = ldap_init(host, (int)conn->port);
    if(server == NULL) {
      failf(data, "LDAP local: Cannot connect to %s:%ld",
            conn->host.dispname, conn->port);
      result = CURLE_COULDNT_CONNECT;
      goto quit;
    }
  }
#ifdef USE_WIN32_LDAP
  ldap_set_option(server, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);
#endif

#ifdef USE_WIN32_LDAP
  rc = ldap_win_bind(conn, server, user, passwd);
#else
  rc = ldap_simple_bind_s(server, user, passwd);
#endif
  if(!ldap_ssl && rc != 0) {
    ldap_proto = LDAP_VERSION2;
    ldap_set_option(server, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);
#ifdef USE_WIN32_LDAP
    rc = ldap_win_bind(conn, server, user, passwd);
#else
    rc = ldap_simple_bind_s(server, user, passwd);
#endif
  }
  if(rc != 0) {
#ifdef USE_WIN32_LDAP
    failf(data, "LDAP local: bind via ldap_win_bind %s",
          ldap_err2string(rc));
#else
    failf(data, "LDAP local: bind via ldap_simple_bind_s %s",
          ldap_err2string(rc));
#endif
    result = CURLE_LDAP_CANNOT_BIND;
    goto quit;
  }

  rc = ldap_search_s(server, ludp->lud_dn, ludp->lud_scope,
                     ludp->lud_filter, ludp->lud_attrs, 0, &ldapmsg);

  if(rc != 0 && rc != LDAP_SIZELIMIT_EXCEEDED) {
    failf(data, "LDAP remote: %s", ldap_err2string(rc));
    result = CURLE_LDAP_SEARCH_FAILED;
    goto quit;
  }

  for(num = 0, entryIterator = ldap_first_entry(server, ldapmsg);
      entryIterator;
      entryIterator = ldap_next_entry(server, entryIterator), num++) {
    BerElement *ber = NULL;
#if defined(USE_WIN32_LDAP)
    TCHAR *attribute;
#else
    char  *attribute;       /*! suspicious that this isn't 'const' */
#endif
    int i;

    /* Get the DN and write it to the client */
    {
      char *name;
      size_t name_len;
#if defined(USE_WIN32_LDAP)
      TCHAR *dn = ldap_get_dn(server, entryIterator);
      name = Curl_convert_tchar_to_UTF8(dn);
      if(!name) {
        ldap_memfree(dn);

        result = CURLE_OUT_OF_MEMORY;

        goto quit;
      }
#else
      char *dn = name = ldap_get_dn(server, entryIterator);
#endif
      name_len = strlen(name);

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"DN: ", 4);
      if(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *) name,
                                 name_len);
      if(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);
      if(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }

      dlsize += name_len + 5;

#if defined(USE_WIN32_LDAP)
      Curl_unicodefree(name);
#endif
      ldap_memfree(dn);
    }

    /* Get the attributes and write them to the client */
    for(attribute = ldap_first_attribute(server, entryIterator, &ber);
        attribute;
        attribute = ldap_next_attribute(server, entryIterator, ber)) {
      BerValue **vals;
      size_t attr_len;
#if defined(USE_WIN32_LDAP)
      char *attr = Curl_convert_tchar_to_UTF8(attribute);
      if(!attr) {
        if(ber)
          ber_free(ber, 0);

        result = CURLE_OUT_OF_MEMORY;

        goto quit;
    }
#else
      char *attr = attribute;
#endif
      attr_len = strlen(attr);

      vals = ldap_get_values_len(server, entryIterator, attribute);
      if(vals != NULL) {
        for(i = 0; (vals[i] != NULL); i++) {
          result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\t", 1);
          if(result) {
            ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
            Curl_unicodefree(attr);
#endif
            ldap_memfree(attribute);
            if(ber)
              ber_free(ber, 0);

            goto quit;
          }

          result = Curl_client_write(conn, CLIENTWRITE_BODY,
                                     (char *) attr, attr_len);
          if(result) {
            ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
            Curl_unicodefree(attr);
#endif
            ldap_memfree(attribute);
            if(ber)
              ber_free(ber, 0);

            goto quit;
          }

          result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)": ", 2);
          if(result) {
            ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
            Curl_unicodefree(attr);
#endif
            ldap_memfree(attribute);
            if(ber)
              ber_free(ber, 0);

            goto quit;
          }

          dlsize += attr_len + 3;

          if((attr_len > 7) &&
             (strcmp(";binary", (char *) attr + (attr_len - 7)) == 0)) {
            /* Binary attribute, encode to base64. */
            result = Curl_base64_encode(data,
                                        vals[i]->bv_val,
                                        vals[i]->bv_len,
                                        &val_b64,
                                        &val_b64_sz);
            if(result) {
              ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
              Curl_unicodefree(attr);
#endif
              ldap_memfree(attribute);
              if(ber)
                ber_free(ber, 0);

              goto quit;
            }

            if(val_b64_sz > 0) {
              result = Curl_client_write(conn, CLIENTWRITE_BODY, val_b64,
                                         val_b64_sz);
              free(val_b64);
              if(result) {
                ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
                Curl_unicodefree(attr);
#endif
                ldap_memfree(attribute);
                if(ber)
                  ber_free(ber, 0);

                goto quit;
              }

              dlsize += val_b64_sz;
            }
          }
          else {
            result = Curl_client_write(conn, CLIENTWRITE_BODY, vals[i]->bv_val,
                                       vals[i]->bv_len);
            if(result) {
              ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
              Curl_unicodefree(attr);
#endif
              ldap_memfree(attribute);
              if(ber)
                ber_free(ber, 0);

              goto quit;
            }

            dlsize += vals[i]->bv_len;
          }

          result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);
          if(result) {
            ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
            Curl_unicodefree(attr);
#endif
            ldap_memfree(attribute);
            if(ber)
              ber_free(ber, 0);

            goto quit;
          }

          dlsize++;
        }

        /* Free memory used to store values */
        ldap_value_free_len(vals);
      }

      /* Free the attribute as we are done with it */
#if defined(USE_WIN32_LDAP)
      Curl_unicodefree(attr);
#endif
      ldap_memfree(attribute);

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);
      if(result)
        goto quit;
      dlsize++;
      Curl_pgrsSetDownloadCounter(data, dlsize);
    }

    if(ber)
       ber_free(ber, 0);
  }

quit:
  if(ldapmsg) {
    ldap_msgfree(ldapmsg);
    LDAP_TRACE(("Received %d entries\n", num));
  }
  if(rc == LDAP_SIZELIMIT_EXCEEDED)
    infof(data, "There are more than %d entries\n", num);
  if(ludp)
    ldap_free_urldesc(ludp);
  if(server)
    ldap_unbind_s(server);
#if defined(HAVE_LDAP_SSL) && defined(CURL_HAS_NOVELL_LDAPSDK)
  if(ldap_ssl)
    ldapssl_client_deinit();
#endif /* HAVE_LDAP_SSL && CURL_HAS_NOVELL_LDAPSDK */

#if defined(USE_WIN32_LDAP)
  Curl_unicodefree(host);
#endif

  /* no data to transfer */
  Curl_setup_transfer(data, -1, -1, FALSE, -1);
  connclose(conn, "LDAP connection always disable re-use");

  return result;
}