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
typedef  int /*<<< orphan*/  ssl_buffer ;
typedef  int /*<<< orphan*/  ssh_buffer ;
typedef  int /*<<< orphan*/  quicbuffer ;
struct TYPE_7__ {int /*<<< orphan*/  version_str; int /*<<< orphan*/  version_num; } ;
typedef  TYPE_1__ nghttp2_info ;
struct TYPE_8__ {char* ssl_version; int ares_num; int iconv_ver_num; char* libssh_version; char* brotli_version; char* quic_version; int /*<<< orphan*/  nghttp2_version; int /*<<< orphan*/  nghttp2_ver_num; int /*<<< orphan*/  brotli_ver_num; int /*<<< orphan*/  features; scalar_t__ libidn; int /*<<< orphan*/  ares; int /*<<< orphan*/  libz_version; } ;
typedef  TYPE_2__ curl_version_info_data ;
typedef  int /*<<< orphan*/  brotli_buffer ;
struct TYPE_9__ {int supports; } ;
typedef  int /*<<< orphan*/  CURLversion ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliDecoderVersion () ; 
 int /*<<< orphan*/  CURL_VERSION_HTTPS_PROXY ; 
 int /*<<< orphan*/  CURL_VERSION_IDN ; 
 int /*<<< orphan*/  Curl_quic_ver (char*,int) ; 
 int /*<<< orphan*/  Curl_ssh_version (char*,int) ; 
 TYPE_6__* Curl_ssl ; 
 int /*<<< orphan*/  Curl_ssl_version (char*,int) ; 
 int /*<<< orphan*/  IDN2_VERSION ; 
 int SSLSUPP_HTTPS_PROXY ; 
 int _LIBICONV_VERSION ; 
 int /*<<< orphan*/  ares_version (int*) ; 
 int /*<<< orphan*/  brotli_version (char*,int) ; 
 scalar_t__ idn2_check_version (int /*<<< orphan*/ ) ; 
 TYPE_1__* nghttp2_version (int /*<<< orphan*/ ) ; 
 TYPE_2__ version_info ; 
 int /*<<< orphan*/  zlibVersion () ; 

curl_version_info_data *curl_version_info(CURLversion stamp)
{
  static bool initialized;
#if defined(USE_SSH)
  static char ssh_buffer[80];
#endif
#ifdef USE_SSL
#ifdef CURL_WITH_MULTI_SSL
  static char ssl_buffer[200];
#else
  static char ssl_buffer[80];
#endif
#endif
#ifdef HAVE_BROTLI
  static char brotli_buffer[80];
#endif

  if(initialized)
    return &version_info;

#ifdef USE_SSL
  Curl_ssl_version(ssl_buffer, sizeof(ssl_buffer));
  version_info.ssl_version = ssl_buffer;
  if(Curl_ssl->supports & SSLSUPP_HTTPS_PROXY)
    version_info.features |= CURL_VERSION_HTTPS_PROXY;
  else
    version_info.features &= ~CURL_VERSION_HTTPS_PROXY;
#endif

#ifdef HAVE_LIBZ
  version_info.libz_version = zlibVersion();
  /* libz left NULL if non-existing */
#endif
#ifdef USE_ARES
  {
    int aresnum;
    version_info.ares = ares_version(&aresnum);
    version_info.ares_num = aresnum;
  }
#endif
#ifdef USE_LIBIDN2
  /* This returns a version string if we use the given version or later,
     otherwise it returns NULL */
  version_info.libidn = idn2_check_version(IDN2_VERSION);
  if(version_info.libidn)
    version_info.features |= CURL_VERSION_IDN;
#elif defined(USE_WIN32_IDN)
  version_info.features |= CURL_VERSION_IDN;
#endif

#if defined(HAVE_ICONV) && defined(CURL_DOES_CONVERSIONS)
#ifdef _LIBICONV_VERSION
  version_info.iconv_ver_num = _LIBICONV_VERSION;
#else
  /* version unknown */
  version_info.iconv_ver_num = -1;
#endif /* _LIBICONV_VERSION */
#endif

#if defined(USE_SSH)
  Curl_ssh_version(ssh_buffer, sizeof(ssh_buffer));
  version_info.libssh_version = ssh_buffer;
#endif

#ifdef HAVE_BROTLI
  version_info.brotli_ver_num = BrotliDecoderVersion();
  brotli_version(brotli_buffer, sizeof(brotli_buffer));
  version_info.brotli_version = brotli_buffer;
#endif

#ifdef USE_NGHTTP2
  {
    nghttp2_info *h2 = nghttp2_version(0);
    version_info.nghttp2_ver_num = h2->version_num;
    version_info.nghttp2_version = h2->version_str;
  }
#endif

#ifdef ENABLE_QUIC
  {
    static char quicbuffer[80];
    Curl_quic_ver(quicbuffer, sizeof(quicbuffer));
    version_info.quic_version = quicbuffer;
  }
#endif

  (void)stamp; /* avoid compiler warnings, we don't use this */

  initialized = true;
  return &version_info;
}