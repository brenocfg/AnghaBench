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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; int flags; } ;
struct atmel_private {int default_key; int* wep_key_len; int wep_is_on; int exclude_unencrypted; int encryption_level; void* pairwise_cipher_suite; int /*<<< orphan*/ * wep_keys; } ;

/* Variables and functions */
 void* CIPHER_SUITE_NONE ; 
 void* CIPHER_SUITE_WEP_128 ; 
 void* CIPHER_SUITE_WEP_64 ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_MODE ; 
 int IW_ENCODE_NOKEY ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_set_encode(struct net_device *dev,
			    struct iw_request_info *info,
			    struct iw_point *dwrq,
			    char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);

	/* Basic checking: do we have a key to set ?
	 * Note : with the new API, it's impossible to get a NULL pointer.
	 * Therefore, we need to check a key size == 0 instead.
	 * New version of iwconfig properly set the IW_ENCODE_NOKEY flag
	 * when no key is present (only change flags), but older versions
	 * don't do it. - Jean II */
	if (dwrq->length > 0) {
		int index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
		int current_index = priv->default_key;
		/* Check the size of the key */
		if (dwrq->length > 13) {
			return -EINVAL;
		}
		/* Check the index (none -> use current) */
		if (index < 0 || index >= 4)
			index = current_index;
		else
			priv->default_key = index;
		/* Set the length */
		if (dwrq->length > 5)
			priv->wep_key_len[index] = 13;
		else
			if (dwrq->length > 0)
				priv->wep_key_len[index] = 5;
			else
				/* Disable the key */
				priv->wep_key_len[index] = 0;
		/* Check if the key is not marked as invalid */
		if (!(dwrq->flags & IW_ENCODE_NOKEY)) {
			/* Cleanup */
			memset(priv->wep_keys[index], 0, 13);
			/* Copy the key in the driver */
			memcpy(priv->wep_keys[index], extra, dwrq->length);
		}
		/* WE specify that if a valid key is set, encryption
		 * should be enabled (user may turn it off later)
		 * This is also how "iwconfig ethX key on" works */
		if (index == current_index &&
		    priv->wep_key_len[index] > 0) {
			priv->wep_is_on = 1;
			priv->exclude_unencrypted = 1;
			if (priv->wep_key_len[index] > 5) {
				priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_128;
				priv->encryption_level = 2;
			} else {
				priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_64;
				priv->encryption_level = 1;
			}
		}
	} else {
		/* Do we want to just set the transmit key index ? */
		int index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
		if (index >= 0 && index < 4) {
			priv->default_key = index;
		} else
			/* Don't complain if only change the mode */
			if (!(dwrq->flags & IW_ENCODE_MODE))
				return -EINVAL;
	}
	/* Read the flags */
	if (dwrq->flags & IW_ENCODE_DISABLED) {
		priv->wep_is_on = 0;
		priv->encryption_level = 0;
		priv->pairwise_cipher_suite = CIPHER_SUITE_NONE;
	} else {
		priv->wep_is_on = 1;
		if (priv->wep_key_len[priv->default_key] > 5) {
			priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_128;
			priv->encryption_level = 2;
		} else {
			priv->pairwise_cipher_suite = CIPHER_SUITE_WEP_64;
			priv->encryption_level = 1;
		}
	}
	if (dwrq->flags & IW_ENCODE_RESTRICTED)
		priv->exclude_unencrypted = 1;
	if (dwrq->flags & IW_ENCODE_OPEN)
		priv->exclude_unencrypted = 0;

	return -EINPROGRESS;		/* Call commit handler */
}