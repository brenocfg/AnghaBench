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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  coap_string_t ;
typedef  int /*<<< orphan*/  coap_session_t ;
typedef  int /*<<< orphan*/  coap_resource_t ;
typedef  int /*<<< orphan*/  coap_pdu_t ;
typedef  int /*<<< orphan*/  coap_context_t ;
typedef  int /*<<< orphan*/  coap_binary_t ;

/* Variables and functions */
 int /*<<< orphan*/  COAP_MEDIATYPE_TEXT_PLAIN ; 
 int /*<<< orphan*/  coap_add_data_blocked_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*) ; 
 scalar_t__ espressif_data ; 
 scalar_t__ espressif_data_len ; 

__attribute__((used)) static void
hnd_espressif_get(coap_context_t *ctx, coap_resource_t *resource,
                  coap_session_t *session,
                  coap_pdu_t *request, coap_binary_t *token,
                  coap_string_t *query, coap_pdu_t *response)
{
    coap_add_data_blocked_response(resource, session, request, response, token,
                                   COAP_MEDIATYPE_TEXT_PLAIN, 0,
                                   (size_t)espressif_data_len,
                                   (const u_char *)espressif_data);
}