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
typedef  int u8 ;
struct ieee80211_device {int* wpa_ie; size_t wpa_ie_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MAX_WPA_IE_LEN ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  printk (char*,size_t,int) ; 

int ieee80211_wx_set_gen_ie(struct ieee80211_device *ieee, u8 *ie, size_t len)
{
	u8 *buf;

	if (len>MAX_WPA_IE_LEN || (len && ie == NULL))
	{
	//	printk("return error out, len:%d\n", len);
	return -EINVAL;
	}


	if (len)
	{
		if (len != ie[1]+2)
		{
			printk("len: %Zd, ie:%d\n", len, ie[1]);
			return -EINVAL;
		}
		buf = kmalloc(len, GFP_KERNEL);
		if (buf == NULL)
			return -ENOMEM;
		memcpy(buf, ie, len);
		kfree(ieee->wpa_ie);
		ieee->wpa_ie = buf;
		ieee->wpa_ie_len = len;
	}
	else{
		if (ieee->wpa_ie)
		kfree(ieee->wpa_ie);
		ieee->wpa_ie = NULL;
		ieee->wpa_ie_len = 0;
	}

	return 0;

}