#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; int numBytes; int isText; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ EmscriptenWebSocketMessageEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  emscripten_websocket_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

EM_BOOL WebSocketMessage(int eventType, const EmscriptenWebSocketMessageEvent *e, void *userData)
{
	printf("message(eventType=%d, userData=%d, data=%p, numBytes=%d, isText=%d)\n", eventType, (int)userData, e->data, e->numBytes, e->isText);
	if (e->isText)
		printf("text data: \"%s\"\n", e->data);
	else
	{
		printf("binary data:");
		for(int i = 0; i < e->numBytes; ++i)
			printf(" %02X", e->data[i]);
		printf("\n");

		emscripten_websocket_delete(e->socket);
		exit(0);
	}
	return 0;
}