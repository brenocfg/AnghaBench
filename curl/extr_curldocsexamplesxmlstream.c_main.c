#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  memory; } ;
struct ParserStruct {int ok; TYPE_1__ characters; int /*<<< orphan*/  tags; } ;
typedef  scalar_t__ XML_Parser ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  CURL_GLOBAL_DEFAULT ; 
 char* XML_ErrorString (int) ; 
 int XML_GetErrorCode (scalar_t__) ; 
 scalar_t__ XML_Parse (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ XML_ParserCreateNS (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  XML_ParserFree (scalar_t__) ; 
 int /*<<< orphan*/  XML_SetCharacterDataHandler (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetElementHandler (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetUserData (scalar_t__,struct ParserStruct*) ; 
 int /*<<< orphan*/  characterDataHandler ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 char* curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endElement ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ParserStruct*,int /*<<< orphan*/ ,int) ; 
 void* parseStreamCallback ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  startElement ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
  CURL *curl_handle;
  CURLcode res;
  XML_Parser parser;
  struct ParserStruct state;

  /* Initialize the state structure for parsing. */
  memset(&state, 0, sizeof(struct ParserStruct));
  state.ok = 1;

  /* Initialize a namespace-aware parser. */
  parser = XML_ParserCreateNS(NULL, '\0');
  XML_SetUserData(parser, &state);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser, characterDataHandler);

  /* Initialize a libcurl handle. */
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL,
                   "https://www.w3schools.com/xml/simple.xml");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, parseStreamCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)parser);

  printf("Depth   Characters   Closing Tag\n");

  /* Perform the request and any follow-up parsing. */
  res = curl_easy_perform(curl_handle);
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else if(state.ok) {
    /* Expat requires one final call to finalize parsing. */
    if(XML_Parse(parser, NULL, 0, 1) == 0) {
      int error_code = XML_GetErrorCode(parser);
      fprintf(stderr, "Finalizing parsing failed with error code %d (%s).\n",
              error_code, XML_ErrorString(error_code));
    }
    else {
      printf("                     --------------\n");
      printf("                     %lu tags total\n", state.tags);
    }
  }

  /* Clean up. */
  free(state.characters.memory);
  XML_ParserFree(parser);
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();

  return 0;
}