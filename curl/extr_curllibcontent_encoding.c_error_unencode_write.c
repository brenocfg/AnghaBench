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
struct connectdata {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  contenc_writer ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_BAD_CONTENT_ENCODING ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 char* Curl_all_content_encodings () ; 
 int /*<<< orphan*/  failf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static CURLcode error_unencode_write(struct connectdata *conn,
                                     contenc_writer *writer,
                                     const char *buf, size_t nbytes)
{
  char *all = Curl_all_content_encodings();

  (void) writer;
  (void) buf;
  (void) nbytes;

  if(!all)
    return CURLE_OUT_OF_MEMORY;
  failf(conn->data, "Unrecognized content encoding type. "
                    "libcurl understands %s content encodings.", all);
  free(all);
  return CURLE_BAD_CONTENT_ENCODING;
}