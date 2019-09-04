#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* url; } ;
typedef  TYPE_1__ EmscriptenWebSocketCreateAttributes ;
typedef  scalar_t__ EMSCRIPTEN_WEBSOCKET_T ;
typedef  int EMSCRIPTEN_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  WebSocketClose ; 
 int /*<<< orphan*/  WebSocketError ; 
 int /*<<< orphan*/  WebSocketMessage ; 
 int /*<<< orphan*/  WebSocketOpen ; 
 int /*<<< orphan*/  emscripten_websocket_init_create_attributes (TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_websocket_is_supported () ; 
 scalar_t__ emscripten_websocket_new (TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_websocket_set_onclose_callback (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_websocket_set_onerror_callback (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_websocket_set_onmessage_callback (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_websocket_set_onopen_callback (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main()
{
	if (!emscripten_websocket_is_supported())
	{
		printf("WebSockets are not supported, cannot continue!\n");
		exit(1);
	}

	EmscriptenWebSocketCreateAttributes attr;
	emscripten_websocket_init_create_attributes(&attr);

	attr.url = "ws://localhost:8080";

	EMSCRIPTEN_WEBSOCKET_T socket = emscripten_websocket_new(&attr);
	if (socket <= 0)
	{
		printf("WebSocket creation failed, error code %d!\n", (EMSCRIPTEN_RESULT)socket);
		exit(1);
	}

	emscripten_websocket_set_onopen_callback(socket, (void*)42, WebSocketOpen);
	emscripten_websocket_set_onclose_callback(socket, (void*)43, WebSocketClose);
	emscripten_websocket_set_onerror_callback(socket, (void*)44, WebSocketError);
	emscripten_websocket_set_onmessage_callback(socket, (void*)45, WebSocketMessage);
}