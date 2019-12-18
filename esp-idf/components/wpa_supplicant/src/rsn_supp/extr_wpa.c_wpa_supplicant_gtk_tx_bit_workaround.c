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
struct wpa_sm {scalar_t__ pairwise_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPA_CIPHER_NONE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int wpa_supplicant_gtk_tx_bit_workaround(const struct wpa_sm *sm,
                        int tx)
{
    if (tx && sm->pairwise_cipher != WPA_CIPHER_NONE) {
        /* Ignore Tx bit for GTK if a pairwise key is used. One AP
         * seemed to set this bit (incorrectly, since Tx is only when
         * doing Group Key only APs) and without this workaround, the
         * data connection does not work because wpa_supplicant
         * configured non-zero keyidx to be used for unicast. */
        #ifdef DEBUG_PRINT     
        wpa_printf(MSG_DEBUG, "WPA: Tx bit set for GTK, but pairwise "
               "keys are used - ignore Tx bit");
        #endif    
        return 0;
    }
    return tx;
}