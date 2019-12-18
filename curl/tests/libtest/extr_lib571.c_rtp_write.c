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
 int /*<<< orphan*/  RTP_DATA ; 
 int RTP_DATA_SIZE ; 
 int RTP_PKT_CHANNEL (char*) ; 
 int RTP_PKT_LENGTH (char*) ; 
 int curlx_uztosi (size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rtp_packet_count ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static size_t rtp_write(void *ptr, size_t size, size_t nmemb, void *stream)
{
  char *data = (char *)ptr;
  int channel = RTP_PKT_CHANNEL(data);
  int message_size;
  int coded_size = RTP_PKT_LENGTH(data);
  size_t failure = (size && nmemb) ? 0 : 1;
  int i;
  (void)stream;

  message_size = curlx_uztosi(size * nmemb) - 4;

  printf("RTP: message size %d, channel %d\n", message_size, channel);
  if(message_size != coded_size) {
    printf("RTP embedded size (%d) does not match the write size (%d).\n",
           coded_size, message_size);
    return failure;
  }

  data += 4;
  for(i = 0; i < message_size; i += RTP_DATA_SIZE) {
    if(message_size - i > RTP_DATA_SIZE) {
      if(memcmp(RTP_DATA, data + i, RTP_DATA_SIZE) != 0) {
        printf("RTP PAYLOAD CORRUPTED [%s]\n", data + i);
        return failure;
      }
    }
    else {
      if(memcmp(RTP_DATA, data + i, message_size - i) != 0) {
        printf("RTP PAYLOAD END CORRUPTED (%d), [%s]\n",
               message_size - i, data + i);
        return failure;
      }
    }
  }

  rtp_packet_count++;
  fprintf(stderr, "packet count is %d\n", rtp_packet_count);

  return size * nmemb;
}