#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int current_speed; struct Curl_easy* headerbuff; struct Curl_easy* buffer; int /*<<< orphan*/  resolver; int /*<<< orphan*/ * lastconnect; scalar_t__ headersize; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct Curl_easy {TYPE_2__ state; TYPE_1__ progress; int /*<<< orphan*/  magic; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLEASY_MAGIC_NUMBER ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_convert_init (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_freeset (struct Curl_easy*) ; 
 scalar_t__ Curl_init_userdefined (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_initinfo (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_resolver_cleanup (int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_resolver_init (struct Curl_easy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 scalar_t__ HEADERSIZE ; 
 int /*<<< orphan*/  PGRS_HIDE ; 
 scalar_t__ READBUFFER_SIZE ; 
 struct Curl_easy* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct Curl_easy*) ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

CURLcode Curl_open(struct Curl_easy **curl)
{
  CURLcode result;
  struct Curl_easy *data;

  /* Very simple start-up: alloc the struct, init it with zeroes and return */
  data = calloc(1, sizeof(struct Curl_easy));
  if(!data) {
    /* this is a very serious error */
    DEBUGF(fprintf(stderr, "Error: calloc of Curl_easy failed\n"));
    return CURLE_OUT_OF_MEMORY;
  }

  data->magic = CURLEASY_MAGIC_NUMBER;

  result = Curl_resolver_init(data, &data->state.resolver);
  if(result) {
    DEBUGF(fprintf(stderr, "Error: resolver_init failed\n"));
    free(data);
    return result;
  }

  /* We do some initial setup here, all those fields that can't be just 0 */

  data->state.buffer = malloc(READBUFFER_SIZE + 1);
  if(!data->state.buffer) {
    DEBUGF(fprintf(stderr, "Error: malloc of buffer failed\n"));
    result = CURLE_OUT_OF_MEMORY;
  }
  else {
    data->state.headerbuff = malloc(HEADERSIZE);
    if(!data->state.headerbuff) {
      DEBUGF(fprintf(stderr, "Error: malloc of headerbuff failed\n"));
      result = CURLE_OUT_OF_MEMORY;
    }
    else {
      result = Curl_init_userdefined(data);

      data->state.headersize = HEADERSIZE;
      Curl_convert_init(data);
      Curl_initinfo(data);

      /* most recent connection is not yet defined */
      data->state.lastconnect = NULL;

      data->progress.flags |= PGRS_HIDE;
      data->state.current_speed = -1; /* init to negative == impossible */
    }
  }

  if(result) {
    Curl_resolver_cleanup(data->state.resolver);
    free(data->state.buffer);
    free(data->state.headerbuff);
    Curl_freeset(data);
    free(data);
    data = NULL;
  }
  else
    *curl = data;

  return result;
}