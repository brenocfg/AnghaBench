__attribute__((used)) static void t6() {
    struct tag6 { int a; } x;
    struct tag6 *p = &x;
    (*p).a = 69;
    expect(69, x.a);
}