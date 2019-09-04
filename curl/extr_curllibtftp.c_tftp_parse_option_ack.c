#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int blksize; long requested_blksize; TYPE_1__* conn; } ;
typedef  TYPE_3__ tftp_state_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  upload; } ;
struct Curl_easy {TYPE_2__ set; } ;
struct TYPE_5__ {struct Curl_easy* data; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_TFTP_ILLEGAL ; 
 int /*<<< orphan*/  Curl_pgrsSetDownloadSize (struct Curl_easy*,long) ; 
 int TFTP_BLKSIZE_DEFAULT ; 
 long TFTP_BLKSIZE_MAX ; 
 long TFTP_BLKSIZE_MIN ; 
 int /*<<< orphan*/  TFTP_OPTION_BLKSIZE ; 
 int /*<<< orphan*/  TFTP_OPTION_TSIZE ; 
 scalar_t__ checkprefix (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,char const*,...) ; 
 long strtol (char const*,int /*<<< orphan*/ *,int) ; 
 char* tftp_option_get (char const*,int,char const**,char const**) ; 

__attribute__((used)) static CURLcode tftp_parse_option_ack(tftp_state_data_t *state,
                                      const char *ptr, int len)
{
  const char *tmp = ptr;
  struct Curl_easy *data = state->conn->data;

  /* if OACK doesn't contain blksize option, the default (512) must be used */
  state->blksize = TFTP_BLKSIZE_DEFAULT;

  while(tmp < ptr + len) {
    const char *option, *value;

    tmp = tftp_option_get(tmp, ptr + len - tmp, &option, &value);
    if(tmp == NULL) {
      failf(data, "Malformed ACK packet, rejecting");
      return CURLE_TFTP_ILLEGAL;
    }

    infof(data, "got option=(%s) value=(%s)\n", option, value);

    if(checkprefix(option, TFTP_OPTION_BLKSIZE)) {
      long blksize;

      blksize = strtol(value, NULL, 10);

      if(!blksize) {
        failf(data, "invalid blocksize value in OACK packet");
        return CURLE_TFTP_ILLEGAL;
      }
      if(blksize > TFTP_BLKSIZE_MAX) {
        failf(data, "%s (%d)", "blksize is larger than max supported",
              TFTP_BLKSIZE_MAX);
        return CURLE_TFTP_ILLEGAL;
      }
      else if(blksize < TFTP_BLKSIZE_MIN) {
        failf(data, "%s (%d)", "blksize is smaller than min supported",
              TFTP_BLKSIZE_MIN);
        return CURLE_TFTP_ILLEGAL;
      }
      else if(blksize > state->requested_blksize) {
        /* could realloc pkt buffers here, but the spec doesn't call out
         * support for the server requesting a bigger blksize than the client
         * requests */
        failf(data, "%s (%ld)",
              "server requested blksize larger than allocated", blksize);
        return CURLE_TFTP_ILLEGAL;
      }

      state->blksize = (int)blksize;
      infof(data, "%s (%d) %s (%d)\n", "blksize parsed from OACK",
            state->blksize, "requested", state->requested_blksize);
    }
    else if(checkprefix(option, TFTP_OPTION_TSIZE)) {
      long tsize = 0;

      tsize = strtol(value, NULL, 10);
      infof(data, "%s (%ld)\n", "tsize parsed from OACK", tsize);

      /* tsize should be ignored on upload: Who cares about the size of the
         remote file? */
      if(!data->set.upload) {
        if(!tsize) {
          failf(data, "invalid tsize -:%s:- value in OACK packet", value);
          return CURLE_TFTP_ILLEGAL;
        }
        Curl_pgrsSetDownloadSize(data, tsize);
      }
    }
  }

  return CURLE_OK;
}