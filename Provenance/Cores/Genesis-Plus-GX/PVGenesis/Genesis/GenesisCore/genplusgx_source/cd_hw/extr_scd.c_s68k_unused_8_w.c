__attribute__((used)) static void s68k_unused_8_w(unsigned int address, unsigned int data)
{
#ifdef LOGERROR
  error("[SUB 68k] Unused write8 %08X = %02X (%08X)\n", address, data, s68k.pc);
#endif
}